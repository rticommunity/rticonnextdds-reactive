using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reactive.Concurrency;
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Disposables;
using RTI.RxDDS;

namespace solar
{
    class SolarSystem
    {
        struct PlanetInfo
        {
            public int orbitRadius;
            public int size;
            public int yearInEarthDays;

            public PlanetInfo(int orbitRadius, int size, int year)
            {
                this.orbitRadius = orbitRadius;
                this.size = size;
                this.yearInEarthDays = year;
            }
        };

        readonly static int earthYear = 365;

        DDS.TypedDataWriter<ShapeType> triangleWriter;
        DDS.TypedDataWriter<ShapeType> circleWriter;
        Dictionary<string, PlanetInfo> planets;

        static void Main(string[] args)
        {
            int domainId = 0;
            IDisposable disposable = null;

            if (args.Length >= 1)
            {
                if (!Int32.TryParse(args[0], out domainId))
                {
                    Console.WriteLine("Invalid domainId. Quitting...");
                    return;
                }
            }

            if (args.Length >= 2)
            {
                if (args[1] == "bigbang")
                    disposable = new SolarSystem(domainId).bigbang();
                else if (args[1] == "bigbang2")
                    disposable = new SolarSystem(domainId).bigbang2();
                else if (args[1] == "bigbang3")
                    disposable = new SolarSystem(domainId).bigbang3();
                else
                {
                    Console.WriteLine("Specify bigbang | bigbang2 | bigbang3. Quitting...");
                    return;
                }
            }

            for (; disposable != null; )
            {
                Console.WriteLine("Press Enter to dispose...");
                ConsoleKeyInfo info = Console.ReadKey(true);
                if (info.Key == ConsoleKey.Enter)
                {
                    disposable.Dispose();
                    break;
                }
            }
        }

        SolarSystem(int domainId)
        {
            planets =
                new Dictionary<string, PlanetInfo>();

            // PlanetInfo(orbitRadius, size, year-in-earth-days)
            planets.Add("Mercury", new PlanetInfo(30,   8,  88));
            planets.Add("Venus",   new PlanetInfo(50,  15,  225));
            planets.Add("Earth",   new PlanetInfo(70,  17,  365));
            planets.Add("Mars",    new PlanetInfo(90,  12,  686));
            planets.Add("Jupiter", new PlanetInfo(120, 30, 4329));
            
            // Yes, the Moon too!
            planets.Add("Moon",    new PlanetInfo(20,  8,  365));

            RTI.RxDDS.DefaultParticipant.DomainId = domainId;

            RTI.RxDDS.DefaultParticipant
                     .RegisterType<ShapeType, 
                                   ShapeTypeTypeSupport>();

            this.triangleWriter =
                RTI.RxDDS.DefaultParticipant
                         .CreateDataWriter<ShapeType>("Triangle");

            this.circleWriter =
                RTI.RxDDS.DefaultParticipant
                         .CreateDataWriter<ShapeType>("Circle");
        }

        ~SolarSystem()
        {
            RTI.RxDDS.DefaultParticipant.Shutdown();
        }        

        ShapeType planetLocation(ShapeType sun, double degree, string planetName)
        {
            var planet = planets[planetName];
            return new ShapeType
            {
                x = sun.x + (int)(planet.orbitRadius * Math.Cos(degree * Math.PI / 180)),
                y = sun.y + (int)(planet.orbitRadius * Math.Sin(degree * Math.PI / 180)),
                color = sun.color,
                shapesize = planet.size
            };
        }

        IDisposable bigbang()
        {
            // The Sun was born here!
            var sunOrbit =
               DDSObservable.FromTopic<ShapeType>(DefaultParticipant.Instance,
                                                  "Square",
                                                  Scheduler.Default);

            // Earth was born here!
            double earthDegree = 0;
            IObservable<ShapeType> earthOrbit =
                    sunOrbit.Select(sunLoc =>
                    {
                        earthDegree+=2;
                        return planetLocation(sunLoc, earthDegree, "Earth");
                    })
                    .Publish()
                    .RefCount();

            // The Moon was born here!
            double moonDegree = 0;
            IObservable<ShapeType> moonOrbit
                = earthOrbit.Select(earthLoc =>
                {
                    moonDegree += 7;
                    return planetLocation(earthLoc, moonDegree, "Moon");
                });

            var assumedInstance = new ShapeType { color = "BLUE" };
            // begin orbiting!
            return new CompositeDisposable(new IDisposable[] { 
                      earthOrbit.DisposeAtEnd(circleWriter, assumedInstance).Subscribe(),
                      moonOrbit.DisposeAtEnd(triangleWriter, assumedInstance).Subscribe()
                  });
        }

        double output(string msg, long t, double degree)
        {
            Console.WriteLine(msg, t, degree);
            return degree;
        }

        IObservable<ShapeType>
                planetOrbitLinq(IObservable<long> ticks,
                                IObservable<ShapeType> sunOrbit,
                                string planetName)
        {
            // This implementation does not propagate dispose
            IObservable<ShapeType> planetOrbit =
                    from t in ticks
                    from sunLoc in sunOrbit.Take(1)
                    let degree = (int)(t * earthYear / planets[planetName].yearInEarthDays)
                    let op = output("t = {0}, degree = {1}", t, degree)
                    select planetLocation(sunLoc, degree, planetName);

            return planetOrbit;
        }

        // Space and Time were born here!
        IDisposable bigbang2()
        {
            // The beginning of time!
            var ticks =
               Observable.Interval(TimeSpan.FromMilliseconds(20),
                                   new EventLoopScheduler());

            // The Sun was born here!
            var sunOrbit =
               DDSObservable.FromTopic<ShapeType>(DefaultParticipant.Instance,
                                                  "Square",
                                                  Scheduler.Default);

            // planets were born here!
            var mercuryOrbit = planetOrbitLinq(ticks, sunOrbit, "Mercury");
            var venusOrbit   = planetOrbitLinq(ticks, sunOrbit, "Venus");
            var earthOrbit   = planetOrbitLinq(ticks, sunOrbit, "Earth").Publish().RefCount();
            var marsOrbit    = planetOrbitLinq(ticks, sunOrbit, "Mars");
            var jupiterOrbit = planetOrbitLinq(ticks, sunOrbit, "Jupiter");

            // The Moon was born here!
            double moonDegree = 0;
            var moonOrbit
                = earthOrbit.Select(earthLoc =>
                {
                    moonDegree += 7;
                    return planetLocation(earthLoc, moonDegree, "Moon");
                });

            // begin orbiting but be ready for the big crunch!
            return new CompositeDisposable(new IDisposable[] { 
                      mercuryOrbit.Subscribe(circleWriter),
                      venusOrbit.Subscribe(circleWriter),
                      earthOrbit.Subscribe(circleWriter),
                      marsOrbit.Subscribe(circleWriter),
                      jupiterOrbit.Subscribe(circleWriter),
                      moonOrbit.Subscribe(triangleWriter)
                  });
        }

        IObservable<ShapeType>
        planetOrbit(IObservable<long> ticks,
                    IObservable<ShapeType> sunOrbit,
                    string planetName)
        {/*
            return ticks.Select(t =>
            {
                var degree = (int)(t * earthYear / planets[planetName].yearInEarthDays);
                Console.WriteLine("t = {0}, degree = {1}", t, degree);
                return sunOrbit.Select(sunLoc => planetLocation(sunLoc, degree, planetName));
            })
            .Switch()
            .Do(planet => Console.WriteLine("x = {0}, y = {1}",  planet.x, planet.y)); ;
            */return planetOrbitLinq(ticks, sunOrbit, planetName);
        }

        IDisposable bigbang3()
        {
            var ticks =
               Observable.Interval(TimeSpan.FromMilliseconds(20),
                                   new EventLoopScheduler());

            var sunOrbitStream =
               DDSObservable.FromKeyedTopic<string, ShapeType>(
                                  DefaultParticipant.Instance,
                                  "Square",
                                  shape => shape.color,
                                  Scheduler.Default);

            return sunOrbitStream.Select(sunOrbit =>
            {
                //var mercuryOrbit = planetOrbit(ticks, sunOrbit, "Mercury");
                //var venusOrbit   = planetOrbit(ticks, sunOrbit, "Venus");
                var earthOrbit   = planetOrbit(ticks, sunOrbit, "Earth").Publish().RefCount();
                //var marsOrbit    = planetOrbit(ticks, sunOrbit, "Mars");
                //var jupiterOrbit = planetOrbit(ticks, sunOrbit, "Jupiter");

                double moonDegree = 0;
                var moonOrbit
                    = earthOrbit.Select(earthLoc =>
                    {
                        moonDegree += 3;
                        Console.WriteLine("moonDegree = {0}", moonDegree);
                        return planetLocation(earthLoc, moonDegree, "Moon");
                    });

                var instance = new ShapeType { color = sunOrbit.Key };
                return new CompositeDisposable(new IDisposable[] { 
                          //mercuryOrbit.DisposeAtEnd(circleWriter,   instance).Subscribe(),
                          //venusOrbit  .DisposeAtEnd(circleWriter,   instance).Subscribe(),
                          earthOrbit  .DisposeAtEnd(circleWriter,   instance).Subscribe(),
                          //marsOrbit   .DisposeAtEnd(circleWriter,   instance).Subscribe(),
                          //jupiterOrbit.DisposeAtEnd(circleWriter,   instance).Subscribe(),
                          moonOrbit   .DisposeAtEnd(triangleWriter, instance).Subscribe()
                      });

            }).Subscribe();
        }
    }
}
