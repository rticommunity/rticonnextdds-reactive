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
using System.Linq;
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Reactive.Concurrency;
using System.Reactive.Disposables;

namespace RTI.RxDDS
{
  public abstract class SubjectOperatorBase<T, U, SubjectType>
    : IObserver<T>, IObservable<U>
      where SubjectType : ISubject<U, U>, new()
  {
    public SubjectOperatorBase(IObservable<T> source)
    {
      this.source = source;
      this.subject = new SubjectType();
    }

    public abstract void OnNext(T value);
    public virtual void OnCompleted()
    {
      subject.OnCompleted();
    }
    public virtual void OnError(Exception error)
    {
      subject.OnError(error);
    }

    public virtual IDisposable Subscribe(IObserver<U> observer)
    {
      return 
        new CompositeDisposable()
        {  
          subject.Subscribe(observer),
          source.Subscribe(this)
        };

      /*      lock (mutex)
      {
        if (!alreadySubscribed)
        {
          alreadySubscribed = true;
          return new CompositeDisposable()
            {  
              disp1,
              source.Subscribe(this)
            };
        }
        else
          return disp1;
      }*/
    }

    //private object mutex;
    //private bool alreadySubscribed = false;
    private IObservable<T> source;
    protected ISubject<U, U> subject;
  };

  public abstract class OperatorBase<T, U> : SubjectOperatorBase<T, U, Subject<U>>
  {
    public OperatorBase(IObservable<T> source)
      : base(source)
    {
    }
  };

  class DataReaderListenerAdapter : DDS.DataReaderListener
  {
    public override void on_requested_deadline_missed(
     DDS.DataReader reader,
     ref DDS.RequestedDeadlineMissedStatus status) { }

    public override void on_requested_incompatible_qos(
        DDS.DataReader reader,
        DDS.RequestedIncompatibleQosStatus status) { }

    public override void on_sample_rejected(
        DDS.DataReader reader,
        ref DDS.SampleRejectedStatus status) { }

    public override void on_liveliness_changed(
        DDS.DataReader reader,
        ref DDS.LivelinessChangedStatus status) { }

    public override void on_sample_lost(
        DDS.DataReader reader,
        ref DDS.SampleLostStatus status) { }

    public override void on_subscription_matched(
        DDS.DataReader reader,
        ref DDS.SubscriptionMatchedStatus status) { }

    public override void on_data_available(
        DDS.DataReader reader) { }
  };

  class ObservableTopic<T> : IObservable<T> where T : class , DDS.ICopyable<T>, new()
  {
    public ObservableTopic(DDS.DomainParticipant participant,
                           string topicName,
                           string typeName,
                           IScheduler subscribeOnScheduler)
    {
      mutex = new Object();

      if (scheduler == null)
        this.scheduler = Scheduler.Immediate;
      else
        this.scheduler = subscribeOnScheduler;
      
      if (typeName == null)
        this.typeName = typeof(T).ToString();
      else
        this.typeName = typeName;

      this.participant = participant;
      this.topicName = topicName;

      if (this.scheduler == null ||
         this.typeName == null ||
         this.participant == null ||
         this.topicName == null)
        throw new ArgumentNullException("ObservableTopic: Null parameters detected");
    }

    public void Dispose()
    {
      listener.Dispose();
    }
    private void initializeDataReader(DDS.DomainParticipant participant)
    {
      DDS.Subscriber subscriber = participant.create_subscriber(
          DDS.DomainParticipant.SUBSCRIBER_QOS_DEFAULT,
          null /* listener */,
          DDS.StatusMask.STATUS_MASK_NONE);
      if (subscriber == null)
      {
        throw new ApplicationException("create_subscriber error");
      }

      DDS.Topic topic = participant.create_topic(
          topicName,
          typeName,
          DDS.DomainParticipant.TOPIC_QOS_DEFAULT,
          null /* listener */,
          DDS.StatusMask.STATUS_MASK_NONE);
      if (topic == null)
      {
        throw new ApplicationException("create_topic error");
      }

      listener = new DataReaderListener(subject, scheduler);
      DDS.DataReaderQos r_qos = new DDS.DataReaderQos();
      participant.get_default_datareader_qos(r_qos);
      //Console.WriteLine("LIB CODE DR QOS: " + r_qos.history.kind);
      //Console.WriteLine("LIB CODE DR QOS: " + r_qos.reliability.kind);
      
        /* To customize the data reader QoS, use 
         the configuration file USER_QOS_PROFILES.xml */
      DDS.DataReader reader = subscriber.create_datareader(
          topic,
          r_qos,//DDS.Subscriber.DATAREADER_QOS_DEFAULT,
          listener,
          DDS.StatusMask.STATUS_MASK_ALL);
     
      if (reader == null)
      {
        listener = null;
        throw new ApplicationException("create_datareader error");
      }
    }

    public IDisposable Subscribe(IObserver<T> observer)
    {
      lock (mutex)
      {
        if (subject == null)
        {
          subject = new Subject<T>();
          initializeDataReader(participant);
        }
      }

      return subject.Subscribe(observer);
    }

    private class DataReaderListener : DataReaderListenerAdapter
    {
      public DataReaderListener(ISubject<T, T> subject, IScheduler scheduler)
      {
        this.subject = subject;
        this.scheduler = scheduler;
        dataSeq = new DDS.UserRefSequence<T>();
        infoSeq = new DDS.SampleInfoSeq();
      }

      public override void on_data_available(DDS.DataReader reader)
      {
        try
        {
          DDS.TypedDataReader<T> dataReader = (DDS.TypedDataReader<T>) reader;

          dataReader.take(
              dataSeq,
              infoSeq,
              DDS.ResourceLimitsQosPolicy.LENGTH_UNLIMITED,
              DDS.SampleStateKind.ANY_SAMPLE_STATE,
              DDS.ViewStateKind.ANY_VIEW_STATE,
              DDS.InstanceStateKind.ANY_INSTANCE_STATE);

              System.Int32 dataLength = dataSeq.length;
             
              for (int i = 0; i < dataLength; ++i)
              {
                if (infoSeq.get_at(i).valid_data)
                {
                  T temp = new T();
                  temp.copy_from(dataSeq.get_at(i));
                  subject.OnNext(temp);
                }
                else if (infoSeq.get_at(i).instance_state ==
                          DDS.InstanceStateKind.NOT_ALIVE_DISPOSED_INSTANCE_STATE)
                {
                 
                  /* FIXME: If the instance comes back online, it will break the Rx contract. */
                  //Console.WriteLine("OnCompleted CALLED FROM LIB CODE on tid "+System.Threading.Thread.CurrentThread.ManagedThreadId);
                  subject.OnCompleted();
                }
              }

              dataReader.return_loan(dataSeq, infoSeq);
        }
        catch (DDS.Retcode_NoData)
        {
            
            subject.OnCompleted();
          return;
        }
        catch (Exception ex)
        {
          subject.OnError(ex);
          Console.WriteLine("ObservableTopic: take error {0}", ex);
        }
      }

      private DDS.UserRefSequence<T> dataSeq;
      private DDS.SampleInfoSeq infoSeq;
      private ISubject<T, T> subject;
      private IScheduler scheduler;
    }

    private Object mutex;
    private DDS.DomainParticipant participant;
    private string topicName;
    private string typeName;
    private DataReaderListener listener;
    private ISubject<T, T> subject;
    private IScheduler scheduler;
  };

  class ObservableKeyedTopic<TKey, T> : IObservable<IGroupedObservable<TKey, T>>
      where T : class , DDS.ICopyable<T>, new()
  {
    public ObservableKeyedTopic(DDS.DomainParticipant participant,
                                string topicName,
                                string typeName,
                                Func<T, TKey> keySelector,
                                IEqualityComparer<TKey> comparer,
                                IScheduler scheduler)
    {
      mutex = new Object();

      if (scheduler == null)
        this.scheduler = Scheduler.Immediate;
      else
        this.scheduler = scheduler;

      if (typeName == null)
        this.typeName = typeof(T).ToString();
      else
        this.typeName = typeName;

      this.participant = participant;
      this.topicName = topicName;      
      this.keySelector = keySelector;
      this.comparer = comparer;
      this.keyedSubjectDict = new Dictionary<TKey, DDSKeyedSubject>(comparer);
      this.handleKeyDict = new Dictionary<DDS.InstanceHandle_t, TKey>(new InstanceHandleComparer());

      if (this.scheduler == null ||
          this.typeName == null ||
          this.participant == null ||
          this.topicName == null ||
          this.keySelector == null ||
          this.comparer == null)
        throw new ApplicationException("Invalid Params");
    }

    public void Dispose()
    {
      listener.Dispose();
    }

    private void initializeDataReader(DDS.DomainParticipant participant)
    {
      DDS.Subscriber subscriber = participant.create_subscriber(
          DDS.DomainParticipant.SUBSCRIBER_QOS_DEFAULT,
          null,
          DDS.StatusMask.STATUS_MASK_NONE);
      if (subscriber == null)
      {
        throw new ApplicationException("create_subscriber error");
      }

      DDS.Topic topic = participant.create_topic(
          topicName,
          typeName,
          DDS.DomainParticipant.TOPIC_QOS_DEFAULT,
          null,
          DDS.StatusMask.STATUS_MASK_NONE);
      if (topic == null)
      {
        throw new ApplicationException("create_topic error");
      }

      listener = new InstanceDataReaderListener(
          groupSubject, keyedSubjectDict, keySelector, comparer, handleKeyDict, scheduler);

      DDS.DataReaderQos r_qos = new DDS.DataReaderQos();
      participant.get_default_datareader_qos(r_qos);
      //Console.WriteLine("LIB CODE DR QOS: " + r_qos.history.kind);
      //Console.WriteLine("LIB CODE DR QOS: " + r_qos.reliability.kind);

      DDS.DataReader reader = subscriber.create_datareader(
          topic,
          r_qos,//DDS.Subscriber.DATAREADER_QOS_DEFAULT,
          listener,
          DDS.StatusMask.STATUS_MASK_ALL);
      if (reader == null)
      {
        listener = null;
        throw new ApplicationException("create_datareader error");
      }
    }

    private void initSubject()
    {
      lock (mutex)
      {
        if (groupSubject == null)
        {
          groupSubject = new Subject<IGroupedObservable<TKey, T>>();
          initializeDataReader(participant);
        }
      }
    }

    public IDisposable Subscribe(IObserver<IGroupedObservable<TKey, T>> observer)
    {
      initSubject();
      return groupSubject.Subscribe(observer);
    }

    public IDisposable Subscribe(Action<IGroupedObservable<TKey, T>> action)
    {
      initSubject();
      return groupSubject.Subscribe(action);
    }

    private class InstanceHandleComparer : IEqualityComparer<DDS.InstanceHandle_t>
    {
      public bool Equals(DDS.InstanceHandle_t h1, DDS.InstanceHandle_t h2)
      {
        return h1.Equals(h2);
      }

      public int GetHashCode(DDS.InstanceHandle_t handle)
      {
        return handle.GetHashCode();
      }
    };
    
    private class DDSKeyedSubject : IGroupedObservable<TKey, T>, IObserver<T>
    {
      public TKey Key
      {
        get
        {
          return this.key;
        }
      }

      public DDSKeyedSubject(TKey key, IScheduler scheduler)
      {
        this.key = key;
        this.scheduler = scheduler;
        this.sub = new Subject<T>();
      }
      public void OnNext(T value)
      {
        //scheduler.Schedule(() => sub.OnNext(value));
        sub.OnNext(value);
      }
      public void OnCompleted()
      {
        //scheduler.Schedule(() => sub.OnCompleted());
        sub.OnCompleted();
      }
      public void OnError(Exception ex)
      {
        //scheduler.Schedule(() => sub.OnError(ex));
        sub.OnError(ex);
      }
      public IDisposable Subscribe(IObserver<T> observer)
      {
        return sub.Subscribe(observer);
      }

      private TKey key;
      private ISubject<T, T> sub;
      private IScheduler scheduler;
    };

    private class InstanceDataReaderListener : DataReaderListenerAdapter
    {
      public InstanceDataReaderListener(IObserver<IGroupedObservable<TKey, T>> observer,
                                        Dictionary<TKey, DDSKeyedSubject> dict,
                                        Func<T, TKey> keySelector,
                                        IEqualityComparer<TKey> comparer,
                                        Dictionary<DDS.InstanceHandle_t, TKey> handleKeyDict,
                                        IScheduler sched)
      {
        this.observer = observer;
        this.scheduler = sched;
        this.keyedSubDict = dict;
        this.keySelector = keySelector;
        this.comparer = comparer;
        this.handleKeyDict = handleKeyDict;
        this.dataSeq = new DDS.UserRefSequence<T>();
        this.infoSeq = new DDS.SampleInfoSeq();
      }

      public override void on_data_available(DDS.DataReader reader)
      {
        try
        {
          DDS.TypedDataReader<T> dataReader =
            (DDS.TypedDataReader<T>)reader;

          dataReader.take(
              dataSeq,
              infoSeq,
              DDS.ResourceLimitsQosPolicy.LENGTH_UNLIMITED,
              DDS.SampleStateKind.ANY_SAMPLE_STATE,
              DDS.ViewStateKind.ANY_VIEW_STATE,
              DDS.InstanceStateKind.ANY_INSTANCE_STATE);

          System.Int32 dataLength = dataSeq.length;
          for (int i = 0; i < dataLength; ++i)
          {
            DDS.SampleInfo info = infoSeq.get_at(i);
            if (info.valid_data)
            {
              T data = new T();
              data.copy_from(dataSeq.get_at(i));
              TKey key = keySelector(data);
              DDSKeyedSubject keyedSubject;

              if (!keyedSubDict.ContainsKey(key))
              {
                keyedSubject = new DDSKeyedSubject(key, scheduler);
                keyedSubDict.Add(key, keyedSubject);
                handleKeyDict.Add(info.instance_handle, key);
                observer.OnNext(keyedSubject);
              }
              else
                keyedSubject = keyedSubDict[key];

              keyedSubject.OnNext(data);
            }
            else if (info.instance_state == DDS.InstanceStateKind.NOT_ALIVE_DISPOSED_INSTANCE_STATE)
            {
              if (handleKeyDict.ContainsKey(info.instance_handle))
              {
                TKey key = handleKeyDict[info.instance_handle];
                if (keyedSubDict.ContainsKey(key))
                {
                  DDSKeyedSubject keyedSub = keyedSubDict[key];
                  keyedSubDict.Remove(key);
                  handleKeyDict.Remove(info.instance_handle);
                  keyedSub.OnCompleted();
                  /* FIXME: If the instance comes alive again, it will break the Rx contract */
                }
                else
                  Console.WriteLine("InstanceDataReaderListener invariant broken: keyedSubDict does not contain key");
              }
              else
                Console.WriteLine("InstanceDataReaderListener invariant broken: handleKeyDict does not contain info.instance_handle");
            }
          }

          dataReader.return_loan(dataSeq, infoSeq);
        }
        catch (DDS.Retcode_NoData)
        {
          return;
        }
        catch (DDS.Exception ex)
        {
          observer.OnError(ex);
          Console.WriteLine("ObservableKeyedTopic: InstanceDataReaderListener: take error {0}", ex);
        }
      }

      private DDS.UserRefSequence<T> dataSeq;
      private DDS.SampleInfoSeq infoSeq;
      private IObserver<IGroupedObservable<TKey, T>> observer;
      private Dictionary<TKey, DDSKeyedSubject> keyedSubDict;
      private Func<T, TKey> keySelector;
      private IEqualityComparer<TKey> comparer;
      private Dictionary<DDS.InstanceHandle_t, TKey> handleKeyDict;
      private IScheduler scheduler;
    }

    private Object mutex;
    private DDS.DomainParticipant participant;
    private string topicName;
    private string typeName;
    private InstanceDataReaderListener listener;
    private ISubject<IGroupedObservable<TKey, T>,
                     IGroupedObservable<TKey, T>> groupSubject;
    private Dictionary<TKey, DDSKeyedSubject> keyedSubjectDict;
    private Func<T, TKey> keySelector;
    private IEqualityComparer<TKey> comparer;
    private Dictionary<DDS.InstanceHandle_t, TKey> handleKeyDict;
    private IScheduler scheduler;
  };


  internal class FixedSizedQueue<T> : ConcurrentQueue<T>
  {
    public long Size { get; private set; }

    public FixedSizedQueue(long size)
    {
      Size = size;
    }

    public bool Shift(T obj, out T outObj)
    {
      base.Enqueue(obj);
      lock (this)
      {
        if ((base.Count > Size) &&
            (base.TryDequeue(out outObj)))
        {
          return true;
        }
        else
        {
          outObj = default(T);
          return false;
        }
      }
    }
  };

  class ActiveKeyScanOp<Key, T, SeedType>
    :  IObserver<IGroupedObservable<Key, T>> ,
       IObservable<IList<IGroupedObservable<Key, T>>>
  {
    public ActiveKeyScanOp(IObservable<IGroupedObservable<Key, T>> source,
                           SeedType seed,
                           Func<SeedType, IList<IGroupedObservable<Key, T>>, SeedType> aggregator)
    {
      this.aggregator = aggregator;
      this.seed = seed;
      this.source = source;
      subject = new Subject<IList<IGroupedObservable<Key, T>>>();
      guard = new Object();
      streamList = new List<IGroupedObservable<Key, T>>();
      completed = false;
    }

    public void OnNext(IGroupedObservable<Key, T> value)
    {
      AddStream(value);
      value.Subscribe(data => { /* OnNext = No-op */},
                      (Exception ex) => DropStream(value),
                      () => DropStream(value));
    }

    public void OnCompleted()
    {
      lock(guard) {
        completed = true;
        if (streamList.Count == 0)
        {
          subject.OnCompleted();
        }
      }
    }

    public void OnError(Exception error)
    {
      subject.OnError(error);
    }

    public virtual IDisposable Subscribe(IObserver<IList<IGroupedObservable<Key, T>>> observer)
    {
      return
        new CompositeDisposable()
        {  
          subject.Subscribe(observer),
          source.Subscribe(this)
        };
    }

    private void AddStream(IGroupedObservable<Key, T> value)
    {
      IList<IGroupedObservable<Key, T>> list = null;
      lock (guard)
      {
        try
        {
          streamList.Add(value);
          list = new List<IGroupedObservable<Key, T>>(streamList);
          this.seed = aggregator(this.seed, list);
        }
        catch (Exception ex)
        {
          this.subject.OnError(ex);
          return;
        }
        /* Ensure Rx contract: Not to invoke observers concurrently.
           Therefore, OnNext call is inside guard. */
        subject.OnNext(list);
      }
    }

    private void DropStream(IGroupedObservable<Key, T> value)
    {
      IList<IGroupedObservable<Key, T>> list = null;
      lock (guard)
      {
        try
        {
          streamList.Remove(value);
          list = new List<IGroupedObservable<Key, T>>(streamList);
          seed = aggregator(this.seed, list);
        }
        catch(Exception ex)
        {
          this.subject.OnError(ex);
          return;
        }
        /* Ensure Rx contract: Not to invoke observers concurrently.
           Therefore, OnNext call is inside guard. */
        subject.OnNext(list);
        if (completed == true)
        {
          subject.OnCompleted();
        }
      }
    }

    private bool completed;
    private Object guard;
    private SeedType seed;
    private IList<IGroupedObservable<Key, T>> streamList;
    private Func<SeedType, IList<IGroupedObservable<Key, T>>, SeedType> aggregator;
    private IObservable<IGroupedObservable<Key, T>> source;
    private Subject<IList<IGroupedObservable<Key, T>>> subject;
  };

  public static class ObservableExtensions
  {
    public static IDisposable Subscribe<TSource>(
        this IObservable<TSource> source,
        DDS.TypedDataWriter<TSource> dw)
    {
      DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;
      return source.Subscribe(
          Observer.Create<TSource>(o => dw.write(o, ref instance_handle)));
    }
    public static IDisposable Subscribe<TSource>(
        this IObservable<TSource> source,
        DDS.TypedDataWriter<TSource> dw,
        Action onCompleted)
    {
      DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;
      return source.Subscribe(
          Observer.Create<TSource>(o => dw.write(o, ref instance_handle), onCompleted));
    }
    public static IDisposable SubscribeAndDisposeOnCompleted<TSource>(
        this IObservable<TSource> source,
        DDS.TypedDataWriter<TSource> dw,
        TSource instance)
    {
      DDS.InstanceHandle_t instance_handle = DDS.InstanceHandle_t.HANDLE_NIL;
      return source.Subscribe(
          Observer.Create<TSource>(o => dw.write(o, ref instance_handle),
                                   () => dw.dispose(instance, ref instance_handle)));
    }
    
    public static IObservable<TSource> Shift<TSource>(
        this IObservable<TSource> source,
        long count,
        IScheduler scheduler)
    {
      return Observable.Create<TSource>(observer =>
      {
        var limited_queue = new FixedSizedQueue<TSource>(count);
        return source.Subscribe(value =>
          {
            TSource outObj;
            if (limited_queue.Shift(value, out outObj))
              observer.OnNext(outObj);
          },
          observer.OnError,
          /* Immediate abort semantics of Rx requires us to propagate
             errors immediately (i.e., without draining the queue).
          (Exception ex) => 
          {
            limited_queue
              .Subscribe(Observer
                         .Create<TSource>(data => observer.OnNext(data),
                                          () => observer.OnError(ex)), 
                                          scheduler);
          }*/
          () =>
          {
            limited_queue.ToObservable(scheduler).Subscribe(observer);
          });
      });
    }
    public static IObservable<TSource> Shift<TSource>(
       this IObservable<TSource> source,
       long count)
    {
      return Shift<TSource>(source, count, Scheduler.Immediate);
    }

    public static IObservable<TAccumulate> RollingAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        TAccumulate seed,
        Func<TAccumulate, TSource, TAccumulate> accumulator)
    {
      return source.Scan<TSource, TAccumulate>(seed, accumulator);
    }

    public static IObservable<TAccumulate> WindowAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        long windowSize,
        TAccumulate seed,
        Func<TAccumulate, TSource, TSource, long, TAccumulate> accumulator,
        Func<TAccumulate, TSource, long, long, TAccumulate> windowDrainer)
    {
      if (accumulator == null)
        throw new ArgumentNullException("WindowAggregate: accumulator can't be null");
      if (windowDrainer == null)
        throw new ArgumentNullException("WindowAggregate: windowDrainer can't be null");

      return Observable.Create<TAccumulate>(observer =>
        {
          FixedSizedQueue<TSource> limitedQueue = new FixedSizedQueue<TSource>(windowSize);

          return source.Subscribe(
            value =>
            {
              try
              {
                TSource outObj;
                if (limitedQueue.Shift(value, out outObj))
                {
                  seed = accumulator(seed, value, outObj, limitedQueue.Count);
                }
                else
                {
                  seed = windowDrainer(seed, value, limitedQueue.Count, limitedQueue.Count - 1);
                }
                observer.OnNext(seed);
              }
              catch (Exception ex)
              {
                observer.OnError(ex);
              }
            },
            observer.OnError,
            () =>
            {
              try
              {
                long count = limitedQueue.Count;
                TSource outObj;
                while(limitedQueue.TryDequeue(out outObj))
                {
                  count--;
                  seed = windowDrainer(seed, outObj, count, count + 1);
                  observer.OnNext(seed);
                }
                if (count != 0)
                  observer.OnError(new ApplicationException("WindowAggregte: OnCompleted: Unable to deque all elements"));
                else
                  observer.OnCompleted();
              }
              catch (Exception ex)
              {
                observer.OnError(ex);
              }
            });
        });
    }
    public static IObservable<TAccumulate> TimeWindowAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        TimeSpan timespan,
        TAccumulate seed,
        Func<TAccumulate, TSource, IList<TSource>, long, TAccumulate> accumulator)
    {
      return TimeWindowAggregate(source, timespan, seed, accumulator, null, Scheduler.Immediate);
    }

    public static IObservable<TAccumulate> TimeWindowAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        TimeSpan timespan,
        TAccumulate seed,
        Func<TAccumulate, TSource, IList<TSource>, long, TAccumulate> accumulator,
        IScheduler scheduler)
    {
      return TimeWindowAggregate(source, timespan, seed, accumulator, null, scheduler);
    }

    public static IObservable<TAccumulate> TimeWindowAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        TimeSpan timespan,
        TAccumulate seed,
        Func<TAccumulate, TSource, IList<TSource>, long, TAccumulate> accumulator,
        Func<TSource, DateTimeOffset> timeKeeper)
    {
      return TimeWindowAggregate(source, timespan, seed, accumulator, timeKeeper, Scheduler.Immediate);
    }

    internal struct TimeStamp<T>
    {
      public DateTimeOffset timestamp;
      public T data;
    };
    
    public static IObservable<TAccumulate> TimeWindowAggregate<TSource, TAccumulate>(
        this IObservable<TSource> source,
        TimeSpan timespan,
        TAccumulate seed,
        Func<TAccumulate, TSource, IList<TSource>, long, TAccumulate> accumulator,
        Func<TSource, DateTimeOffset> timeKeeper,
        IScheduler scheduler)
    {
      if (accumulator == null)
        throw new ArgumentNullException("TimeWindowAggregate: accumulator can't be null");

      return Observable.Create<TAccumulate>(observer =>
      {
        List<TimeStamp<TSource>> timestampList = new List<TimeStamp<TSource>>();
        IList<TSource> expiredList = new List<TSource>();

        return source.Subscribe(value => {
          try
          {
            DateTimeOffset now;
            if (timeKeeper != null)
              now = timeKeeper(value);
            else
              now = Scheduler.Now;

            int exCount = 0;
            expiredList.Clear();
            foreach (var item in timestampList)
            {
              if ((now - item.timestamp) > timespan)
              {
                exCount++;
                expiredList.Add(item.data);
              }
              else
                break;
            }
            timestampList.RemoveRange(0, exCount);
            timestampList.Add(new TimeStamp<TSource>
            {
              timestamp = now,
              data = value
            });
            seed = accumulator(seed, value, expiredList, timestampList.Count);
            observer.OnNext(seed);
          }
          catch (Exception ex)
          {
            observer.OnError(ex);
          }
        }, 
        observer.OnError, 
        observer.OnCompleted);
      });
    }

    public static IObservable<TSource> Do<TSource>(
        this IObservable<TSource> source,
        Action<TSource, long> action)
    {
      return Observable.Create<TSource>(observer => {
        long count = 1;
        return source.Do(data => action(data, count++))
                     .Subscribe(observer);
      });
    }
    public static IObservable<TSource> DoIf<TSource>
        (this IObservable<TSource> source,
        Func<bool> conditional,
        Action<TSource> action)
    {
        if (!conditional())
            return source;
        else
            return Observable.Create<TSource>(observer =>
                {
                    return source.Do(d => action(d)).Subscribe(observer);
                });
    }
    public static IObservable<TSource> DoIf<TSource>
      (this IObservable<TSource> source,
      Func<bool> conditional,
      Action<TSource> action,Action onCompleted)
    {
        if (!conditional())
            return source;
        else
            return Observable.Create<TSource>(observer =>
            {
                return source
                    .Do(d => action(d),()=>onCompleted())
                    .Subscribe(observer);
            });
    }
          

    public static IDisposable OnDataAvailable<TSource>(
        this IObservable<TSource> source,
        Action<TSource> onNext,
        Action onCompleted)
    {
      return source.Subscribe(onNext, onCompleted);
    }
    public static IDisposable OnDataAvailable<TSource>(
        this IObservable<TSource> source,
        Action<TSource> onNext)
    {
      return source.Subscribe(onNext);
    }
    public static IDisposable OnDataAvailable<TSource>(
        this IObservable<TSource> source,
        DDS.TypedDataWriter<TSource> dw)
    {
      return source.Subscribe(dw);
    }
    public static IEnumerable<U> Scan<T, U>(this IEnumerable<T> input, Func<U, T, U> next, U state)
    {
      yield return state;
      foreach (var item in input)
      {
        state = next(state, item);
        yield return state;
      }
    }

    public static IObservable<IList<IGroupedObservable<Key, T>>> ActiveKeyScan<Key, T, Seed>(
       this IObservable<IGroupedObservable<Key, T>> source,
       Seed seed,
       Func<Seed, IList<IGroupedObservable<Key, T>>, Seed> aggregator)
    {
      return new ActiveKeyScanOp<Key, T, Seed>(source, seed, aggregator);
    }

    public static IObservable<T> Once<T>(this IObservable<T> source, T first, IScheduler scheduler)
    {
      return Observable.Create<T>(observer =>
      {
        scheduler.Schedule(() => observer.OnNext(first));
        return source.Subscribe(observer);
      });
    }

    public static IObservable<T> Once<T>(this IObservable<T> source, T first)
    {
      return Once<T>(source, first, Scheduler.Immediate);
    }
    public static IObservable<T> Once<T>(this IObservable<T> source, Func<T> onceAction, IScheduler scheduler)
    {
      return Observable.Create<T>(observer =>
      {
        scheduler.Schedule(() => observer.OnNext(onceAction()));
        return source.Subscribe(observer);
      });
    }
    public static IObservable<T> Once<T>(this IObservable<T> source, Func<T> onceAction)
    {
      return Once<T>(source, onceAction, Scheduler.Immediate);
    }
  };

  public static class DDSObservable
  {
    public static IObservable<T> FromTopic<T>(DDS.DomainParticipant participant,
                                              string topicName,
                                              IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable = new ObservableTopic<T>(participant, topicName, null, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }

    public static IObservable<T> FromTopic<T>(DDS.DomainParticipant participant,
                                              string topicName,
                                              string typeName,
                                              IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable = new ObservableTopic<T>(participant, topicName, typeName, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }

    public static IObservable<IGroupedObservable<TKey, T>>
        FromKeyedTopic<TKey, T>(DDS.DomainParticipant participant,
                                string topicName,
                                Func<T, TKey> keySelector,
                                IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable =
        new ObservableKeyedTopic<TKey, T>(participant, topicName, null, keySelector, EqualityComparer<TKey>.Default, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }

    public static IObservable<IGroupedObservable<TKey, T>>
        FromKeyedTopic<TKey, T>(DDS.DomainParticipant participant,
                                string topicName,
                                string typeName,
                                Func<T, TKey> keySelector,
                                IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable =
        new ObservableKeyedTopic<TKey, T>(participant, topicName, typeName, keySelector, EqualityComparer<TKey>.Default, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }

    public static IObservable<IGroupedObservable<TKey, T>>
        FromKeyedTopic<TKey, T>(DDS.DomainParticipant participant,
                                string topicName,
                                Func<T, TKey> keySelector,
                                IEqualityComparer<TKey> keyComparer,
                                IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable =
        new ObservableKeyedTopic<TKey, T>(participant, topicName, null, keySelector, keyComparer, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }
    public static IObservable<IGroupedObservable<TKey, T>>
        FromKeyedTopic<TKey, T>(DDS.DomainParticipant participant,
                                string topicName,
                                string typeName,
                                Func<T, TKey> keySelector,
                                IEqualityComparer<TKey> keyComparer,
                                IScheduler subscribeOnScheduler = null)
        where T : class , DDS.ICopyable<T>, new()
    {
      var ddsObservable =
        new ObservableKeyedTopic<TKey, T>(participant, topicName, typeName, keySelector, keyComparer, Scheduler.Immediate);
      if (subscribeOnScheduler == null)
        return ddsObservable;
      else
        return ddsObservable.SubscribeOn(subscribeOnScheduler);
    }
  };

  public class DefaultParticipant
  {
    public static int DomainId
    {
      get { return domainId; }
      set { domainId = value; }
    }

    public static DDS.DomainParticipant Instance
    {
      get
      {
        if (participant == null)
        {
           
          participant =
              DDS.DomainParticipantFactory.get_instance().create_participant(
                  domainId,
                  DDS.DomainParticipantFactory.PARTICIPANT_QOS_DEFAULT,
                  null /* listener */,
                  DDS.StatusMask.STATUS_MASK_NONE);
          if (participant == null)
          {
            throw new ApplicationException("create_participant error");
          }
        }

        return participant;
      }
    }

    public static void Shutdown()
    {
      if (Instance != null)
      {
        Instance.delete_contained_entities();
        DDS.DomainParticipantFactory.get_instance().delete_participant(
            ref participant);
      }
    }

    public static void RegisterType<Type, TypeSupportClass>()
    {
        typeof(TypeSupportClass)
          .GetMethod("register_type",
                     System.Reflection.BindingFlags.Public |
                     System.Reflection.BindingFlags.Static)        
         .Invoke(null, new Object[] { Instance, typeof(Type).ToString() });
    }
    
    public static DDS.TypedDataWriter<T> CreateDataWriter<T>(string topicName)
    {
      return CreateDataWriter<T>(topicName, typeof(T).ToString());
    }
    public static DDS.TypedDataWriter<T> CreateDataWriter<T>(string topicName, 
                                                             string typeName)
    {
      DDS.DomainParticipant participant = Instance;

      DDS.Publisher publisher = participant.create_publisher(
          DDS.DomainParticipant.PUBLISHER_QOS_DEFAULT,
          null /* listener */,
          DDS.StatusMask.STATUS_MASK_NONE);

      if (publisher == null)
      {
        throw new ApplicationException("create_publisher error");
      }

      DDS.Topic topic = participant.create_topic(
          topicName,
          typeName,
          DDS.DomainParticipant.TOPIC_QOS_DEFAULT,
          null /* listener */,
          DDS.StatusMask.STATUS_MASK_NONE);
      
      if (topic == null)
      {
        throw new ApplicationException("create_topic error");
      }
     /* DDS.DataWriterQos dw_qos = new DDS.DataWriterQos();
      participant.get_default_datawriter_qos(dw_qos);
      dw_qos.reliability.kind = DDS.ReliabilityQosPolicyKind.RELIABLE_RELIABILITY_QOS;
      dw_qos.history.kind = DDS.HistoryQosPolicyKind.KEEP_ALL_HISTORY_QOS;*/
      DDS.DataWriterQos dw_qos = new DDS.DataWriterQos();
      participant.get_default_datawriter_qos(dw_qos);
      //Console.WriteLine("LIB CODE DW QOS: " + dw_qos.history.kind);
      //Console.WriteLine("LIB CODE DW QOS: " + dw_qos.reliability.kind);

      DDS.DataWriter writer = publisher.create_datawriter(
          topic,
          DDS.Publisher.DATAWRITER_QOS_DEFAULT,
          null /* listener */,
          DDS.StatusMask.STATUS_MASK_NONE);
      if (writer == null)
      {
        throw new ApplicationException("create_datawriter error");
      }

      return (DDS.TypedDataWriter<T>) writer;
    }

    private static DDS.DomainParticipant participant;
    private static int domainId = 0;
  };
}