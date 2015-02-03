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
            public string color;
            public int orbitRadius;
            public int size;
            public int yearInEarthDays;

            public PlanetInfo(string color, int radius, int size, int year)
            {
                this.color = color;
                this.orbitRadius = radius;
                this.size = size;
                this.yearInEarthDays = year;
            }
        };

        readonly static int earthYear = 365;

        DDS.TypedDataWriter<ShapeTypeExtended> triangleWriter;
        DDS.TypedDataWriter<ShapeTypeExtended> circleWriter;
        Dictionary<string, PlanetInfo> planets;

        static void Main(string[] args)
        {
            int domainId = 0;

            if (args.Length >= 1)
            {
                if (!Int32.TryParse(args[0], out domainId))
                {
                    Console.WriteLine("Invalid domainId. Quitting...");
                    return;
                }
            }

            var solarSystem = new SolarSystem(domainId);
            var disposable = solarSystem.bigbang();

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

            planets.Add("Mercury", new PlanetInfo("RED",     30,  8,  88));
            planets.Add("Venus",   new PlanetInfo("YELLOW",  50, 15,  225));
            planets.Add("Earth",   new PlanetInfo("BLUE",    70, 17,  365));
            planets.Add("Mars",    new PlanetInfo("ORANGE",  90, 12,  686));
            planets.Add("Jupiter", new PlanetInfo("CYAN",   120, 30, 4329));
            
            // Yes, the Moon too!
            planets.Add("Moon",    new PlanetInfo("GREEN",   20,  8,  365));

            RTI.RxDDS.DefaultParticipant.DomainId = domainId;

            RTI.RxDDS.DefaultParticipant
                     .RegisterType<ShapeTypeExtended, 
                                   ShapeTypeExtendedTypeSupport>();

            this.triangleWriter =
                RTI.RxDDS.DefaultParticipant
                         .CreateDataWriter<ShapeTypeExtended>("Triangle");

            this.circleWriter =
                RTI.RxDDS.DefaultParticipant
                         .CreateDataWriter<ShapeTypeExtended>("Circle");
        }

        ~SolarSystem()
        {
            RTI.RxDDS.DefaultParticipant.Shutdown();
        }        

        ShapeTypeExtended planetLocation(ShapeTypeExtended sunLoc, 
                                         long degree, 
                                         string planetName)
        {
            return new ShapeTypeExtended
            {
                x = sunLoc.x + (int)(planets[planetName].orbitRadius * Math.Cos(degree * Math.PI / 180)),
                y = sunLoc.y + (int)(planets[planetName].orbitRadius * Math.Sin(degree * Math.PI / 180)),
                color = planets[planetName].color,
                shapesize = planets[planetName].size
            };
        }

        IObservable<ShapeTypeExtended>
                        planetOrbit(IObservable<long> ticks, 
                                    IObservable<ShapeTypeExtended> sunOrbit,
                                    string planetName)
        {
            var planetOrbit =
                    from t in ticks
                    from sunLoc in sunOrbit.Take(1)
                    let degree = (int)(t * earthYear / planets[planetName].yearInEarthDays)
                    select planetLocation(sunLoc, degree, planetName);
                
            return planetOrbit;
        }

        // Space and Time were born here!
        IDisposable bigbang()
        {
            // The beginning of time!
            var ticks =
               Observable.Interval(TimeSpan.FromMilliseconds(20), new EventLoopScheduler());

            // The Sun was born here!
            var sunOrbit =
               DDSObservable.FromTopic<ShapeTypeExtended>(DefaultParticipant.Instance, 
                                                          "Square", 
                                                          Scheduler.Default);

            // planets were born here!
            var mercuryOrbit = planetOrbit(ticks, sunOrbit, "Mercury");
            var venusOrbit   = planetOrbit(ticks, sunOrbit, "Venus");
            var earthOrbit   = planetOrbit(ticks, sunOrbit, "Earth");
            var marsOrbit    = planetOrbit(ticks, sunOrbit, "Mars");
            var jupiterOrbit = planetOrbit(ticks, sunOrbit, "Jupiter");

            // The Moon was born here!
            long degree = 0;
            var moonOrbit
                = earthOrbit.Select(earthLoc =>
                              {
                                  degree += 7;
                                  return planetLocation(earthLoc, degree, "Moon");
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
    }
}
