/*********************************************************************************************
(c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.                                  
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Reactive.Concurrency;
using System.Reactive.Disposables;
using RTI.RxDDS;

public class Processor
{

  private ShapeTypeExtended[] test_shape_vals = new ShapeTypeExtended[10] {
          new ShapeTypeExtended { x = 50,  y = 50,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 51,  y = 51,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 52,  y = 52,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 53,  y = 53,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 54,  y = 54,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 55,  y = 55,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 56,  y = 56,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 57,  y = 57,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 58,  y = 58,  color="BLUE", shapesize = 30  },
          new ShapeTypeExtended { x = 59,  y = 59,  color="BLUE", shapesize = 30  },
        };

  public static void Main(string[] args)
  {
    DefaultParticipant.DomainId = 0;

    if (args.Length >= 1)
    {
      int domainId = 0;
      if (!Int32.TryParse(args[0], out domainId))
      {
        Console.WriteLine("Invalid domainId. Quitting...");
        return;
      }
      DefaultParticipant.DomainId = domainId;
    }
    
    DDS.DomainParticipant participant = DefaultParticipant.Instance;

    try
    {
      DefaultParticipant.RegisterType<ShapeTypeExtended, ShapeTypeExtendedTypeSupport>();

      Processor proc = new Processor();
      proc.triangle_writer =
        DefaultParticipant.CreateDataWriter<ShapeTypeExtended>("Triangle");

      proc.circle_writer =
        DefaultParticipant.CreateDataWriter<ShapeTypeExtended>("Circle");

      IDisposable disposable = null;

      //int workerThreads, completionPortThreads;
      //System.Threading.ThreadPool.GetMaxThreads(out workerThreads, out completionPortThreads);
      //Console.WriteLine("# of workerThreads = {0}, # of completionPortThreads = {1} ", 
      //                  workerThreads, completionPortThreads);

      IScheduler scheduler;
      if (args.Length >= 3)
      {
        if (args[2] == "Default")
          scheduler = Scheduler.Default;
        else if (args[2] == "ThreadPool")
          scheduler = Scheduler.Default;
        else if (args[2] == "Immediate")
          scheduler = Scheduler.Immediate;
        else if (args[2] == "CurrentThread")
          scheduler = Scheduler.CurrentThread;
        else if (args[2] == "TaskPool")
          scheduler = TaskPoolScheduler.Default;
        else if (args[2] == "EventLoop")
          scheduler = new EventLoopScheduler();
        else
          throw new ApplicationException("Unknown Scheduler!");
      }
      else
        scheduler = Scheduler.Immediate;

      if (args.Length >= 2)
      {
        if (args[1] == "demo1")
          disposable = proc.demo1(participant, scheduler);
        if (args[1] == "demo2")
          disposable = proc.demo2(participant, scheduler);
        if (args[1] == "demo3")
          disposable = proc.demo3(participant);
        if (args[1] == "demo4")
          disposable = proc.demo4(participant);
        if (args[1] == "demo5")
          disposable = proc.demo5(participant, scheduler);
        if (args[1] == "forward")
          disposable = proc.forward(participant);
        else if (args[1] == "forward_short")
          disposable = proc.forward_short(participant);
        else if (args[1] == "forward_shortest")
          disposable = proc.forward_shortest(participant);
        else if (args[1] == "swap")
          disposable = proc.swap(participant);
        else if (args[1] == "swap_shortest")
          disposable = proc.swap(participant);
        else if (args[1] == "flower")
          disposable = proc.flower(participant);
        else if (args[1] == "instance_forward")
          disposable = proc.instance_forward(participant);
        else if (args[1] == "aggregator")
          disposable = proc.aggregator(participant);
        else if (args[1] == "collisions_combinelatest")
          disposable = proc.collisions_combinelatest(participant, scheduler);
        else if (args[1] == "collisions")
          disposable = proc.collisions(participant, scheduler);
        else if (args[1] == "single_circle_correlator")
          disposable = proc.single_circle_correlator(participant);
        else if (args[1] == "selectmany_correlator")
          disposable = proc.selectmany_correlator(participant, false);
        else if (args[1] == "selectmany_correlator_linq")
          disposable = proc.selectmany_correlator(participant, true);
        else if (args[1] == "selectmany_groupby_correlator")
          disposable = proc.selectmany_groupby_correlator(participant);
        else if (args[1] == "many_circle_correlator")
          disposable = proc.many_circle_correlator(participant, scheduler);
        else if (args[1] == "circle_zip_correlator")
          disposable = proc.circle_zip_correlator(participant);
        else if (args[1] == "splitterDelayNAverageWindow")
          disposable = proc.splitterDelayNAverageWindow(participant);
        else if (args[1] == "splitterDelayNAverage")
          disposable = proc.splitterDelayNAverage(participant);
        else if (args[1] == "timeWindowAggregator")
          disposable = proc.timeWindowAggregator(participant, scheduler);
        else if (args[1] == "key_correlator_flat")
          disposable = proc.key_correlator_flat(participant);
        else if (args[1] == "key_correlator_grouped")
          disposable = proc.key_correlator_grouped(participant);
        else if (args[1] == "key_correlator_replay")
          disposable = proc.key_correlator_replay(participant, false);
        else if (args[1] == "key_correlator_replay_linq")
          disposable = proc.key_correlator_replay(participant, true);
        else if (args[1] == "key_correlator_zip4")
          disposable = proc.key_correlator_zip4(participant);
        else if (args[1] == "key_correlator_zipN")
        {
          int n = 8;
          if (args.Length == 2)
            n = Int32.Parse(args[1]);

          disposable = proc.key_correlator_zipN(participant, n);
        }
        else if (args[1] == "key_correlator_dynamic")
          disposable = proc.key_correlator_dynamic(participant, scheduler);
        else if (args[1] == "once")
            disposable = proc.once(participant);
        else if (args[1] == "join")
            disposable = proc.join(participant);
        else if (args[1] == "orbit")
            disposable = proc.orbit(participant);
        else if (args[1] == "orbitSquare")
            disposable = proc.orbitSquare(participant);
        else if (args[1] == "orbitTwo")
            disposable = proc.orbitTwo(participant);
        else if (args[1] == "solarSystem")
            disposable = proc.solarSystem(participant);
        else if (args[1] == "shapewriter")
            disposable = proc.shapewriter(participant);
        else if (args[1] == "groupJoinInfiniteInner")
            disposable = proc.groupJoinInfiniteInner();
      }

      for (; disposable != null; )
      {
        ConsoleKeyInfo info = Console.ReadKey(true);
        if (info.Key == ConsoleKey.Enter)
        {
          disposable.Dispose();
          break;
        }
      }
    }
    catch (DDS.Exception e)
    {
      Console.WriteLine("DDS Exception {0}", e);
    }
    catch (Exception ex)
    {
      Console.WriteLine("Generic Exception {0}", ex);
    }
    Console.WriteLine("Quitting...");
    System.Threading.Thread.Sleep(1000);
    DefaultParticipant.Shutdown();
  }

  /* forward */
  IDisposable demo1(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_reader = DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");

    IDisposable disposable =
        rx_reader.OnDataAvailable((ShapeTypeExtended shape) =>
        {
          DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
          triangle_writer.write(shape, ref handle);
        });

    return disposable;
  }

  /* forward_short */
  IDisposable demo2(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    // In this example Scheduler.Default appears to be indistinguishable from Scheduler.TaskPool.
    return
    DDSObservable
        .FromTopic<ShapeTypeExtended>(participant, "Square")
        .Subscribe((ShapeTypeExtended shape) =>
        {
          DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
          triangle_writer.write(shape, ref handle);
        });
  }

  /* forward_shortest */
  IDisposable demo3(DDS.DomainParticipant participant)
  {
    DDS.Duration_t timeout;
    timeout.nanosec = 0;
    timeout.sec = 10;

    return DDSObservable
            .FromTopicWaitSet<ShapeTypeExtended>(participant, "Square", timeout)
            .Subscribe(triangle_writer);
  }

  /* swap */
  IDisposable demo4(DDS.DomainParticipant participant)
  {
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");

    return
    rx_square_reader.Select((ShapeTypeExtended shape) =>
    {
      return new ShapeTypeExtended
      {
        x = shape.y,
        y = shape.x,
        color = shape.color,
        shapesize = shape.shapesize
      };
    }).SubscribeAndDisposeOnCompleted(triangle_writer,
                                    new ShapeTypeExtended { color = "BLUE" });

  }

  /* correlator */
  IDisposable demo5(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

    var correlator =
        from square in rx_square_reader
        from circle in rx_circle_reader.Take(1)
        where square.color == circle.color
        select new ShapeTypeExtended
        {
          x = square.x,
          y = square.y,
          color = square.color,
          shapesize = circle.x
        };

    return correlator.Do(_ => Console.WriteLine("ThreadId = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
                     .Subscribe(triangle_writer);
  }

  IDisposable timeWindowAggregator(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(
            participant, "Square", shape => shape.color);
    //test_shape_vals.ToObservable().GroupBy(shape => shape.color);

    /* Extremely stable memory consumption */
    return
        rx_square_reader
        .Subscribe((IGroupedObservable<string, ShapeTypeExtended> square_instance) =>
        {
          square_instance
              .ObserveOn(scheduler)
              .TimeWindowAggregate(
                  TimeSpan.FromSeconds(2),
                  new { avgX = 0.0, avgY = 0.0, shape = new ShapeTypeExtended() },
                  (avg, curVal, expiredList, curCount) =>
                  {
                    double totalX = avg.avgX * (curCount + expiredList.Count - 1);
                    double totalY = avg.avgY * (curCount + expiredList.Count - 1);
                    totalX += curVal.x;
                    totalY += curVal.y;
                    foreach (var ex in expiredList)
                    {
                      totalX -= ex.x;
                      totalY -= ex.y;
                    }
                    return new
                    {
                      avgX = totalX / curCount,
                      avgY = totalY / curCount,
                      shape = curVal
                    };
                  })
              .Select(point =>
                  new ShapeTypeExtended
                  {
                    x = (int)point.avgX,
                    y = (int)point.avgY,
                    color = square_instance.Key,
                    shapesize = point.shape.shapesize
                  })
              .SubscribeAndDisposeOnCompleted(triangle_writer,
                                              new ShapeTypeExtended { color = square_instance.Key });
        });
  }

  IDisposable aggregator(DDS.DomainParticipant participant)
  {
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle");

    return new CompositeDisposable(
         new IDisposable[] {
                 rx_square_reader.Subscribe(triangle_writer),
                 rx_circle_reader.Subscribe(triangle_writer)
             }
    );
  }

  IDisposable splitterDelayNAverageWindow(DDS.DomainParticipant participant)
  {
    long WINDOW_SIZE = 50;
    long HISTORY_SIZE = 20;

    //circle_writer = DefaultParticipant.CreateDataWriter<ShapeTypeExtended>("Circle");
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(
            participant, "Square", shape => shape.color);
    // test_shape_vals.ToObservable().GroupBy(shape => shape.color);

    return new CompositeDisposable(
                new IDisposable[] {
                       rx_square_reader
                          .Subscribe(square_instance => 
                                     square_instance
                                       .Shift(HISTORY_SIZE)
                                       .SubscribeAndDisposeOnCompleted(circle_writer,
                                                    new ShapeTypeExtended { color = square_instance.Key } )),
                       rx_square_reader
                          .Subscribe(square_instance =>
                              {
                                  square_instance.Zip(
                                    square_instance
                                    .Select(square => square.x)
                                    .WindowAggregate(WINDOW_SIZE,
                                                     0.0,
                                                     (avgX, tail, head, count) => (avgX * count + tail - head) / count,
                                                     (avgX, tail, count, prevCount) =>
                                                     {
                                                         if (prevCount > count) tail *= -1;
                                                         return (avgX * prevCount + tail) / count;
                                                     }),
                                    square_instance
                                    .Select(square => square.y)
                                    .WindowAggregate(WINDOW_SIZE,
                                                     0.0,
                                                     (avgY, tail, head, count) => (avgY * count + tail - head) / count,
                                                     (avgY, tail, count, prevCount) => 
                                                        {
                                                            if (prevCount > count) tail *= -1;
                                                            return (avgY * prevCount + tail) / count;
                                                        }),
                                   (square, avgX, avgY) =>
                                       new ShapeTypeExtended
                                       {
                                           x = (int) avgX,
                                           y = (int) avgY,
                                           shapesize = square.shapesize,
                                           color = square.color
                                       })
                                .SubscribeAndDisposeOnCompleted(triangle_writer, 
                                                              new ShapeTypeExtended { color = square_instance.Key});
                              })
                    });
  }

  IDisposable splitterDelayNAverage(DDS.DomainParticipant participant)
  {
    //circle_writer = DefaultParticipant.CreateDataWriter<ShapeTypeExtended>("Circle");

    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");
    int MAX_HISTORY = 20;
    int countX = 0, countY = 0;

    // var rx_square_reader = Observable.Range(10, 100);
    return new CompositeDisposable(
                new IDisposable[] {
                       rx_square_reader
                          .Shift(MAX_HISTORY)
                          .SubscribeAndDisposeOnCompleted(circle_writer, new ShapeTypeExtended { color = "BLUE" }),

                       rx_square_reader.Zip(
                          rx_square_reader
                            .Select(square => square.x)
                            .RollingAggregate(0.0, 
                                              (avgX, x) => 
                                              {
                                                  avgX = ((avgX * countX) + x) / (countX+1);
                                                  countX++;
                                                  return avgX;
                                              }),
                          rx_square_reader
                            .Select(square => square.y)
                            .RollingAggregate(0.0, 
                                              (avgY, y) => 
                                              {
                                                  avgY = ((avgY * countY) + y) / (countY+1);
                                                  countY++;
                                                  return avgY;
                                              }),
                          (square, avgX, avgY) => 
                              new ShapeTypeExtended { 
                                  x = (int) avgX, 
                                  y = (int) avgY, 
                                  shapesize = square.shapesize, 
                                  color = square.color })
                          .Subscribe(triangle_writer)
                    });
  }


  IDisposable many_circle_correlator(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);
    var map = new Dictionary<string, int>();

    rx_circle_reader
        .GroupBy(circle => circle.color)
        .ObserveOn(scheduler)
        .Subscribe(grouped_circle =>
        {
          grouped_circle
            .Do(circle =>
            {
              lock (map)
              {
                map[grouped_circle.Key] = circle.x;
              }
            })
            .Subscribe();
        });

    return
        rx_square_reader
        .GroupBy(shape => shape.color)
        .ObserveOn(scheduler)
        .Do(grouped_square =>
        {
          lock (map)
          {
            map[grouped_square.Key] = 45;
          }
        })
        .Subscribe(grouped_square =>
        {
          grouped_square
              .Select(square =>
              {
                return new ShapeTypeExtended
                {
                  x = square.x,
                  y = square.y,
                  color = grouped_square.Key,
                  shapesize = map[grouped_square.Key]
                };
              })
              .Subscribe(triangle_writer);
        });
  }

  IDisposable circle_zip_correlator(DDS.DomainParticipant participant)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", sq => sq.color, Scheduler.Default);
    var map = new Dictionary<string, int>();

    IScheduler scheduler = new EventLoopScheduler();

    Console.WriteLine("Main Thread id = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId);
    return
        rx_square_reader
      //.GroupBy(shape => shape.color)
        .Do(_ => Console.WriteLine("Before ObserveOn tid = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
        .ObserveOn(scheduler)
        .Do(_ => Console.WriteLine("After ObserveOn tid = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
        .Subscribe(grouped_square =>
        {
          Console.WriteLine("Inner Thread id = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId);
          grouped_square
                .Do(_ => Console.WriteLine("Before Zip tid = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
                .Zip(rx_circle_reader
                       .Do(_ => Console.WriteLine("Circle tid = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
                       .Where(circle => circle.color == grouped_square.Key),
                     (square, circle) =>
                     {
                       return new ShapeTypeExtended
                       {
                         x = square.x,
                         y = square.y,
                         color = grouped_square.Key,
                         shapesize = circle.x
                       };
                     })
                .Do(_ => Console.WriteLine("After Zip tid = {0}", System.Threading.Thread.CurrentThread.ManagedThreadId))
                .Subscribe(shape => Console.WriteLine("{0} {1}", shape.x, shape.y));
        });
  }

  IDisposable selectmany_correlator(DDS.DomainParticipant participant, bool useLinq)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

    if (useLinq)
    {
      var correlator =
          from square in rx_square_reader
          from circle in rx_circle_reader.Take(1)
          where square.color == circle.color
          select new ShapeTypeExtended
          {
            x = square.x,
            y = square.y,
            color = square.color,
            shapesize = circle.x
          };

      return correlator.Subscribe(triangle_writer);
    }
    else
    {
      /* Consumes unbounded amount of memory. Don't know why. */
      return
          rx_square_reader
              .ObserveOn(Scheduler.Default)
              .SelectMany(square =>
              {
                return
                    rx_circle_reader
                        .Where(circle => circle.color == square.color)
                        .Take(1)
                        .Select(circle =>
                            new ShapeTypeExtended
                            {
                              x = square.x,
                              y = square.y,
                              color = square.color,
                              shapesize = circle.x
                            });
              })
              .Subscribe(triangle_writer);
    }
  }

  IDisposable selectmany_groupby_correlator(DDS.DomainParticipant participant)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

    /* Very stable memory consumption */
    return
        rx_square_reader
        .GroupBy(shape => shape.color)
        .Subscribe(grouped_square =>
        {
          grouped_square
              .ObserveOn(Scheduler.Default)
              .SelectMany(square =>
              {
                return rx_circle_reader
                    .Where(circle => circle.color == grouped_square.Key)
                    .Take(1)
                    .Select(circle =>
                        new ShapeTypeExtended
                        {
                          x = square.x,
                          y = square.y,
                          color = grouped_square.Key,
                          shapesize = circle.x
                        });
              })
              .Subscribe(triangle_writer);
        });
  }

  IDisposable single_circle_correlator(DDS.DomainParticipant participant)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle");
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");

    int size = 45;
    rx_circle_reader.Subscribe(circle => size = circle.x);

    return
        rx_square_reader
        .GroupBy(shape => shape.color)
        .Subscribe(grouped_square =>
        {
          grouped_square
              .Select(square =>
              {
                return new ShapeTypeExtended
                {
                  x = square.x,
                  y = square.y,
                  color = grouped_square.Key,
                  shapesize = size
                };
              })
              .Subscribe(triangle_writer);
        });
  }

  IDisposable forward(DDS.DomainParticipant participant)
  {
    var rx_reader = DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");

    IDisposable disposable =
        rx_reader.OnDataAvailable((ShapeTypeExtended shape) =>
        {
          DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
          triangle_writer.write(shape, ref handle);
        });

    return disposable;
  }

  IDisposable forward_short(DDS.DomainParticipant participant)
  {
    return DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square")
                .OnDataAvailable((ShapeTypeExtended shape) =>
                {
                  DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
                  triangle_writer.write(shape, ref handle);
                });
  }
  IDisposable forward_shortest(DDS.DomainParticipant participant)
  {
    return DDSObservable
                .FromTopic<ShapeTypeExtended>(participant, "Square")
                .OnDataAvailable(triangle_writer);
  }

  IDisposable swap(DDS.DomainParticipant participant)
  {
    return DDSObservable
                .FromTopic<ShapeTypeExtended>(participant, "Square")
                .Select(shape => new ShapeTypeExtended
                {
                  x = shape.y,
                  y = shape.x,
                  color = shape.color,
                  shapesize = shape.shapesize
                })
                .SubscribeAndDisposeOnCompleted(triangle_writer,
                                                new ShapeTypeExtended { color = "BLUE" });
  }

  IDisposable instance_forward(DDS.DomainParticipant participant)
  {
    DDS.Duration_t timeout = new DDS.Duration_t();
    timeout.nanosec = 0;
    timeout.sec = 10;
    return DDSObservable.FromKeyedTopicWaitSet<string, ShapeTypeExtended>
            (participant, "Square", shape => shape.color, timeout)
                  .Subscribe(dds_instance =>
                  {
                    ShapeTypeExtended key = new ShapeTypeExtended { color = dds_instance.Key };
                    DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
                    dds_instance.Subscribe(triangle_writer,
                                           () => triangle_writer.dispose(key, ref handle));
                  });
  }

  IDisposable flower(DDS.DomainParticipant participant)
  {
      int a = 30, b = 30, c = 10;

      return Observable.Interval(TimeSpan.FromMilliseconds(1), Scheduler.Immediate)
                       .Select((long x) =>
                       {
                           int angle = (int)(x % 360);
                           return new ShapeTypeExtended
                           {
                               x = (int)(120 + (a + b) * Math.Cos(angle) + b * Math.Cos((a / b - c) * angle)),
                               y = (int)(120 + (a + b) * Math.Sin(angle) + b * Math.Sin((a / b - c) * angle)),
                               color = "GREEN",
                               shapesize = 5
                           };
                       })
                       .Subscribe(triangle_writer);
  }

  IDisposable orbit(DDS.DomainParticipant participant)
  {
      int radius = 40, a = 100, b = 100;

      var rx_square_reader
          = DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

      return Observable.Interval(TimeSpan.FromMilliseconds(3), Scheduler.Immediate)
                       .Select((long i) =>
                       {
                           int angle = (int)(i % 360);
                            return new ShapeTypeExtended
                            {
                                x = a + (int)(radius * Math.Cos(angle * Math.PI / 180)),
                                y = b + (int)(radius * Math.Sin(angle * Math.PI / 180)),
                                color = "RED",
                                shapesize = 10
                            };
                       })
                       .Subscribe(circle_writer);
  }

  IDisposable orbitSquare(DDS.DomainParticipant participant)
  {
      int radius = 40;

      var rx_square_reader
          = DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

      return Observable.Interval(TimeSpan.FromMilliseconds(3), Scheduler.Immediate)
                       .SelectMany((long i) =>
                       {
                           int angle = (int)(i % 360);
                           return
                               rx_square_reader
                               .Select(shape =>
                               {
                                   return new ShapeTypeExtended
                                   {
                                       x = shape.x + (int)(radius * Math.Cos(angle * Math.PI / 180)),
                                       y = shape.y + (int)(radius * Math.Sin(angle * Math.PI / 180)),
                                       color = "RED",
                                       shapesize = 10
                                   };
                               }).Take(1);
                       })
                       .Subscribe(circle_writer);
  }

  IDisposable orbitTwo(DDS.DomainParticipant participant)
  {
      int circle_radius = 60;
      int triangle_radius = 30;

      var rx_square_reader
          = DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

      var circle_orbit =
          Observable.Interval(TimeSpan.FromMilliseconds(8), new EventLoopScheduler())
                       .SelectMany((long i) =>
                       {
                           int degree = (int)(i % 360);
                           return
                               rx_square_reader
                               .Select(shape =>
                               {
                                   return new ShapeTypeExtended
                                   {
                                       x = shape.x + (int)(circle_radius * Math.Cos(degree * Math.PI / 180)),
                                       y = shape.y + (int)(circle_radius * Math.Sin(degree * Math.PI / 180)),
                                       color = "RED",
                                       shapesize = 15
                                   };
                               }).Take(1);
                       });

      int angle = 0;
      var triangle_orbit
          = circle_orbit
                .Select(shape =>
                {
                    angle += 3;
                    if (angle >= 360)
                        angle = 0;
                    return new ShapeTypeExtended
                    {
                        x = shape.x + (int)(triangle_radius * Math.Cos(angle * Math.PI / 180)),
                        y = shape.y + (int)(triangle_radius * Math.Sin(angle * Math.PI / 180)),
                        color = "YELLOW",
                        shapesize = 10
                    };
                });

      return new CompositeDisposable(new IDisposable[] { 
          triangle_orbit.Subscribe(triangle_writer),
          circle_orbit.Subscribe(circle_writer)
      });
  }

  IDisposable shapewriter(DDS.DomainParticipant participant)
  {
      var square_writer =
          DefaultParticipant.CreateDataWriter<ShapeTypeExtended>("Square");

      for (int i = 0; i < test_shape_vals.Length; ++i)
      {
          Console.WriteLine("Press Enter to write Square.");
          ConsoleKeyInfo info = Console.ReadKey(true);
          if (info.Key == ConsoleKey.Enter)
          {
              DDS.InstanceHandle_t handle = DDS.InstanceHandle_t.HANDLE_NIL;
              var shape = test_shape_vals[i];
              square_writer.write(shape, ref handle);
              Console.WriteLine("x = {0}, y = {0}", shape.x, shape.y);
          }
      }


      return Disposable.Create(() => {});
  }

  IDisposable solarSystem(DDS.DomainParticipant participant)
  {
      var sunLoc =
          DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

      var ticks =
        Observable.Interval(TimeSpan.FromMilliseconds(25), new EventLoopScheduler());

      Func<string, int, int, int, IObservable<ShapeTypeExtended>> planetOrbit
          = (color, size, orbitRadius, daysInYear) =>
          {
              var useLinq = false;
              if (useLinq)
              {
                  return from t in ticks
                         from sun in sunLoc.Take(1)
                         let degree = (int)(t * 365 / daysInYear)
                         select new ShapeTypeExtended
                         {
                             x = sun.x + (int)(orbitRadius * Math.Cos(degree * Math.PI / 180)),
                             y = sun.y + (int)(orbitRadius * Math.Sin(degree * Math.PI / 180)),
                             color = color,
                             shapesize = size
                         };
              }
              else
              {
                  double degree = 0;
                  return ticks
                           .SelectMany((long i) =>
                           {
                               degree = (double)i * 365 / daysInYear;
                               return
                                   sunLoc
                                   .Take(1)
                                   .Select(shape =>
                                   {
                                       Console.WriteLine("i = {0}, degree = {1}, x = {2}, y = {3}", i, degree, shape.x, shape.y);
                                       return new ShapeTypeExtended
                                       {
                                           x = shape.x + (int)(orbitRadius * Math.Cos(degree * Math.PI / 180)),
                                           y = shape.y + (int)(orbitRadius * Math.Sin(degree * Math.PI / 180)),
                                           color = color,
                                           shapesize = size
                                       };
                                   });
                           });
              }
          };

      int mercuryRadius = 30,  mercurySize  = 8,  mercuryYear = 88;
      int venusRadius   = 50,  venusSize    = 15, venusYear   = 225;
      int earthRadius   = 70,  earthSize    = 17, earthYear   = 365;
      int marsRadius    = 90,  marsSize     = 12, marsYear    = 686;
      int jupiterRadius = 120, jupiterSize  = 30, jupiterYear = 4329;
      int moonRadius    = 20,  moonSize     = 8;

      //var mercuryLoc = planetOrbit("RED",    mercurySize, mercuryRadius, mercuryYear);
      //var venusLoc   = planetOrbit("YELLOW", venusSize,   venusRadius,   venusYear);
      var earthLoc   = planetOrbit("BLUE",   earthSize,   earthRadius,   earthYear);
      //var marsLoc    = planetOrbit("ORANGE", marsSize,    marsRadius,    marsYear);
      //var jupiterLoc = planetOrbit("CYAN",   jupiterSize, jupiterRadius, jupiterYear);

      int angle = 0;
      var moonLoc
          = earthLoc
                .Select(shape =>
                {
                    angle += 3;
                    return new ShapeTypeExtended
                    {
                        x = shape.x + (int)(moonRadius * Math.Cos(angle * Math.PI / 180)),
                        y = shape.y + (int)(moonRadius * Math.Sin(angle * Math.PI / 180)),
                        color = "GREEN",
                        shapesize = moonSize
                    };
                });
      
      return new CompositeDisposable(new IDisposable[] { 
          //mercuryLoc.Subscribe(circle_writer),
          //venusLoc.Subscribe(circle_writer),
          earthLoc.Subscribe(circle_writer)
          //marsLoc.Subscribe(circle_writer),
          //jupiterLoc.Subscribe(circle_writer),
          // moonLoc.Subscribe(triangle_writer)
      });
  }

  double distance(int x1, int y1, int x2, int y2)
  {
    return Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
  }

  IDisposable collisions(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);
    /*
            var collisions =  from circle in rx_circle_reader
                              from square in rx_square_reader.Take(30) 
                              where square.color == circle.color
                                    &&
                                    distance(circle.x, circle.y, square.x, square.y) <= 30
                              select new ShapeTypeExtended 
                              { 
                                  x = (circle.x + square.x) / 2, 
                                  y = (circle.y + square.y) / 2,
                                  color = "GREEN",
                                  shapesize = 10
                              }; 

            return collisions.Subscribe(triangle_writer);
    */
    /*
            return
                rx_circle_reader
                  .Where(circle => circle.color == "BLUE")
                  .SelectMany(circle => rx_square_reader.Where(square => square.color == "RED").Take(30),
                              (circle, square) => new { x1 = circle.x, y1 = circle.y, x2 = square.x, y2 = square.y })
                  .Where(point => distance(point.x1, point.y1, point.x2, point.y2) <= 30)
                  .Select(p =>
                  {
                      return new ShapeTypeExtended
                      {
                          x = (p.x1 + p.x2) / 2,
                          y = (p.y1 + p.y2) / 2,
                          color = "GREEN",
                          shapesize = 10
                      };
                  })
                  .Subscribe(triangle_writer);
    */
    /* Very stable memory usage */
    return
        rx_circle_reader
          .ObserveOn(scheduler)
          .SelectMany(circle =>
          {
            return
                rx_square_reader
                 .Take(1)
                 .Where(square => square.color == circle.color)
                 .Where(square => distance(square.x, square.y, circle.x, circle.y) <= 30)
                 .Select(square =>
                 {
                   return new ShapeTypeExtended
                   {
                     x = (square.x + circle.x) / 2,
                     y = (square.y + circle.y) / 2,
                     color = "RED",
                     shapesize = 10
                   };
                 });
          })
          .Subscribe(triangle_writer);

  }

  IDisposable collisions_combinelatest(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_circle_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle", Scheduler.Default);
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square", Scheduler.Default);

    var dummy = new ShapeTypeExtended { color = "DUMMY" };

    return rx_circle_reader
              .ObserveOn(scheduler)
              .CombineLatest(rx_square_reader,
                             (circle, square) =>
                             {
                               if (distance(circle.x, circle.y, square.x, square.y) <= 30)
                                 return new ShapeTypeExtended
                                 {
                                   x = (square.x + circle.x) / 2,
                                   y = (square.y + circle.y) / 2,
                                   color = "RED",
                                   shapesize = 10
                                 };
                               else
                                 return dummy;
                             })
                 .Where(shape => shape.color != "DUMMY")
                 .Subscribe(triangle_writer);
  }

  IDisposable key_correlator_flat(DDS.DomainParticipant participant)
  {
    var rx_square_reader =
        DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square");

    var disp1 =
       rx_square_reader
            .Where(shape => shape.color == "GREEN")
            .CombineLatest(rx_square_reader.Where(shape => shape.color == "BLUE"),
                          (a, b) =>
                          {
                            return new ShapeTypeExtended
                            {
                              x = (int)((a.x + b.x) / 2),
                              y = (int)((a.y + b.y) / 2),
                              color = "RED",
                              shapesize = a.shapesize
                            };
                          })
              .Subscribe(triangle_writer);

    var disp2 =
      rx_square_reader
          .Where(shape => shape.color == "YELLOW")
          .CombineLatest(rx_square_reader.Where(shape => shape.color == "MAGENTA"),
                        (a, b) =>
                        {
                          return new ShapeTypeExtended
                          {
                            x = (int)((a.x + b.x) / 2),
                            y = (int)((a.y + b.y) / 2),
                            color = "CYAN",
                            shapesize = a.shapesize
                          };
                        })
            .Subscribe(triangle_writer);


    return new CompositeDisposable(new IDisposable[] { disp1, disp2 });
  }

  IDisposable key_correlator_grouped(DDS.DomainParticipant participant)
  {
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", shape => shape.color);

    var color_observable_map =
      new Dictionary<string, IGroupedObservable<string, ShapeTypeExtended>>();

    var associations = new Dictionary<string, string>();
    associations.Add("PURPLE", "BLUE");
    associations.Add("BLUE", "PURPLE");
    associations.Add("RED", "GREEN");
    associations.Add("GREEN", "RED");
    associations.Add("YELLOW", "CYAN");
    associations.Add("CYAN", "YELLOW");
    associations.Add("MAGENTA", "ORANGE");
    associations.Add("ORANGE", "MAGENTA");

    /* Increasing memory consumption */
    return
      rx_square_reader
        .Do(groupedSq => color_observable_map.Add(groupedSq.Key, groupedSq))
        .Subscribe(groupedSq =>
        {
          var pair_key = associations[groupedSq.Key];
          if (color_observable_map.ContainsKey(pair_key))
          {
            groupedSq
              .CombineLatest(color_observable_map[pair_key],
                            (a, b) =>
                            {
                              return new ShapeTypeExtended
                              {
                                x = (int)((a.x + b.x) / 2),
                                y = (int)((a.y + b.y) / 2),
                                color = a.color,
                                shapesize = a.shapesize
                              };
                            })
              .Subscribe(triangle_writer);
          }
        });
  }

  IDisposable key_correlator_replay(DDS.DomainParticipant participant, bool useLinq)
  {
    int MAX_COLORS = 8;

    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", shape => shape.color);

    var dictionary = new Dictionary<string, string>();
    dictionary.Add("PURPLE", "BLUE");
    dictionary.Add("RED", "GREEN");
    dictionary.Add("YELLOW", "CYAN");
    dictionary.Add("MAGENTA", "ORANGE");

    var associations = new ReadOnlyDictionary<string, string>(dictionary);

    var cache = rx_square_reader.Replay();
    cache.Connect();

    if (useLinq)
    {
      return
          (from group1 in cache.Where(groupedSq => associations.ContainsKey(groupedSq.Key))
           from group2 in cache.Take(MAX_COLORS)
           where associations[group1.Key] == group2.Key
           select new { k1 = group1, k2 = group2 })
            .Subscribe(pair =>
            {
              Console.WriteLine("MATCH {0}--{1}", pair.k1.Key, pair.k2.Key);
              pair.k1.CombineLatest(pair.k2,
                                   (a, b) =>
                                   {
                                     return new ShapeTypeExtended
                                     {
                                       x = (int)((a.x + b.x) / 2),
                                       y = (int)((a.y + b.y) / 2),
                                       color = a.color,
                                       shapesize = a.shapesize
                                     };
                                   })
                     .Subscribe(triangle_writer);
            });
    }
    else
    {
      return
        cache
           .Where(groupedSq => associations.ContainsKey(groupedSq.Key))
           .SelectMany(groupedSq => cache.Take(MAX_COLORS),
                      (groupedSq, cached_groupedSq) =>
                      {
                        if (associations[groupedSq.Key] == cached_groupedSq.Key)
                        {
                          Console.WriteLine("MATCH {0} -- {1}", groupedSq.Key, cached_groupedSq.Key);
                          groupedSq
                            .CombineLatest(cached_groupedSq,
                                          (a, b) =>
                                          {
                                            return new ShapeTypeExtended
                                            {
                                              x = (int)((a.x + b.x) / 2),
                                              y = (int)((a.y + b.y) / 2),
                                              color = a.color,
                                              shapesize = a.shapesize
                                            };
                                          })
                            .Subscribe(triangle_writer);
                        }
                        else
                          Console.WriteLine("NO-MATCH {0} -- {1}", groupedSq.Key, cached_groupedSq.Key);

                        return (IGroupedObservable<string, ShapeTypeExtended>)groupedSq;
                      }).Subscribe();
    }
  }
  IDisposable key_correlator_zip4(DDS.DomainParticipant participant)
  {
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", shape => shape.color);

    var color_map = new Dictionary<string, IObservable<IGroupedObservable<string, ShapeTypeExtended>>>();

    color_map.Add("BLUE", rx_square_reader.Where(sq => sq.Key == "BLUE"));
    color_map.Add("RED", rx_square_reader.Where(sq => sq.Key == "RED"));
    color_map.Add("GREEN", rx_square_reader.Where(sq => sq.Key == "GREEN"));
    color_map.Add("YELLOW", rx_square_reader.Where(sq => sq.Key == "YELLOW"));

    return
      color_map["RED"]
              .Zip(color_map["GREEN"],
                   color_map["BLUE"],
                   color_map["YELLOW"],
                  (rs, gs, bs, ys) =>
                  {
                    rs.CombineLatest(gs, bs, ys,
                                      (r, g, b, y) =>
                                      {
                                        return new ShapeTypeExtended
                                        {
                                          x = (r.x + g.x + b.x + y.x) / 4,
                                          y = (r.y + g.y + b.y + y.y) / 4,
                                          color = "MAGENTA",
                                          shapesize = 30
                                        };
                                      })
                        .Subscribe(triangle_writer);

                    return rs;
                  }).Subscribe();
  }

  IDisposable key_correlator_zipN(DDS.DomainParticipant participant, int N)
  {
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", shape => shape.color);

    // The order of the keys is the same that of the Shapes Demo UI.
    var allkeys = new string[] { "PURPLE", "BLUE", "RED", "GREEN", "YELLOW", "CYAN", "MAGENTA", "ORANGE" };
    var nkeys = allkeys.Take(N);

    Console.Write("Averaging {0}: ", N);
    nkeys.Subscribe(Observer.Create<string>(key => Console.Write("{0} ", key)));
    Console.WriteLine();

    var color_observables =
      nkeys.Select(key => rx_square_reader.Where(sq => sq.Key == key));

    return
    Observable.Zip(color_observables)
              .Subscribe((IList<IGroupedObservable<string, ShapeTypeExtended>> key_list) =>
              {
                Observable.CombineLatest(key_list)
                          .Select((IList<ShapeTypeExtended> shapes) =>
                          {
                            var avg = new ShapeTypeExtended
                            {
                              x = 0,
                              y = 0,
                              color = "RED",
                              shapesize = 30
                            };

                            foreach (var shape in shapes)
                            {
                              avg.x += shape.x;
                              avg.y += shape.y;
                            }
                            avg.x /= shapes.Count;
                            avg.y /= shapes.Count;

                            return avg;
                          })
                          .Subscribe(triangle_writer);
              });
  }

  IDisposable key_correlator_dynamic(DDS.DomainParticipant participant, IScheduler scheduler)
  {
    var rx_square_reader =
        DDSObservable.FromKeyedTopic<string, ShapeTypeExtended>(participant, "Square", shape => shape.color, scheduler);
    var triangleColor = "RED";
    
    return
      rx_square_reader
        .ActiveKeyScan(new { lastSub = Disposable.Empty },
            (seed, stream_list) =>
            {
              seed.lastSub.Dispose();
              if (stream_list.Count == 0)
              {
                var handle = DDS.InstanceHandle_t.HANDLE_NIL;
                triangle_writer.dispose(new ShapeTypeExtended { color = triangleColor }, ref handle);
                return new { lastSub = Disposable.Empty };
              }
              else
                return new
                {
                  lastSub =
                    Observable.CombineLatest(stream_list)
                              .Select((IList<ShapeTypeExtended> shapes) =>
                              {
                                var avg = new ShapeTypeExtended
                                {
                                  x = 0,
                                  y = 0,
                                  color = triangleColor,
                                  shapesize = 30
                                };

                                foreach (var shape in shapes)
                                {
                                  avg.x += shape.x;
                                  avg.y += shape.y;
                                }
                                avg.x /= shapes.Count;
                                avg.y /= shapes.Count;

                                return avg;
                              })
                              .Subscribe(triangle_writer)
                };
            })
        .Subscribe();
  }

  IDisposable once(DDS.DomainParticipant participant)
  {
      return Observable
              .Timer(TimeSpan.FromSeconds(1), TimeSpan.FromSeconds(1))
              .Once(10)
              .Once(() => 20)
              .Subscribe(Console.WriteLine);
  }

  IDisposable join(DDS.DomainParticipant participant)
  {
      var squares =
          DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Square")
                       .Publish()
                       .RefCount();
      var circles =
          DDSObservable.FromTopic<ShapeTypeExtended>(participant, "Circle")
                       .Publish()
                       .RefCount();

      /* Check if the shapes jump more than 1 pixel at a time.*/
      /* Yes, they do if fast. */
      
      ShapeTypeExtended dummy = null;
      squares.Scan(new 
                   {
                         lastx = -1, 
                         lasty = -1, 
                         shape = dummy,
                         largeDiff = false
                   },
                   (seed, shape) =>
                   {
                       return new {
                         lastx = shape.x,
                         lasty = shape.y,
                         shape = shape,
                         largeDiff = (Math.Abs(seed.lastx - shape.x) > 1) ||
                                     (Math.Abs(seed.lasty - shape.y) > 1)
                       };
                   })
             .Where(obj => obj.largeDiff)
             .Subscribe(obj =>
                   {
                        Console.WriteLine("{0} {1}", obj.shape.x, obj.shape.y);
                   });
      
      return squares.ObserveOn(Scheduler.Default)
                    .Join(circles, 
                          _ => squares, 
                          _ => circles,
                          (square, circle) => new { 
                              sq = square, 
                              cr = circle
                          })
                    .Where(obj => (obj.sq.x == obj.cr.x) || 
                                  (obj.sq.y == obj.cr.y))
                    .Select(obj => new ShapeTypeExtended
                          {
                              x = obj.sq.x,
                              y = obj.sq.y,
                              color = "GREEN",
                              shapesize = 15
                          })
                    .Subscribe(triangle_writer);
  }

  public static IEnumerable<int> Numbers()
  {
    int i = 0;
    while (true)
    {
      yield return unchecked(i++);
    }
  }
  IDisposable groupJoinInfiniteInner()
  {
    var xs = new int[] { 0, 1, 2, 3 };
    var ys = Enumerable.Repeat(0, 1000000000).Scan((n, _) => n + 1, 0);
    //IEnumerable<int> ys = Numbers();
    var result = xs.GroupJoin(ys,
                                x => x % 2 == 0,
                                y => y % 2 == 0,
                                (x, g) => g.Take(5))
                     .Take(1).SelectMany(x => x);

    //foreach(var r in result)
    //  Console.WriteLine("{0}", r);

    return Disposable.Empty;
  }

  private DDS.TypedDataWriter<ShapeTypeExtended> square_writer;
  private DDS.TypedDataWriter<ShapeTypeExtended> triangle_writer;
  private DDS.TypedDataWriter<ShapeTypeExtended> circle_writer;
  private DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;
}


