using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reactive.Concurrency;

namespace SoccerExtesions
{
  class TimeWindowAggregatorForTsDataOp<T, TAccumulate> : RTI.RxDDS.OperatorBase<T, TAccumulate>
  {

    public TimeWindowAggregatorForTsDataOp(IObservable<T> source,
                                  Int64 timespan,
                                  string field_name,
                                  TAccumulate seed,
                                  Func<TAccumulate, T, IList<T>, long, TAccumulate> accumulator)
      : base(source)
    {
      timestamp_list = new List<T>();
      this.timespan = timespan;
      Seed = seed;
      Accumulator = accumulator;
      mField_name = field_name;
    }

    public override void OnNext(T value)
    {
      int ex_count = 0;
      IList<T> expiredList = new List<T>();
      foreach (var item in timestamp_list)
      {
        Int64 currentTs = (Int64)value.GetType().GetField(mField_name).GetValue(value);
        Int64 itemTs = (Int64)value.GetType().GetField(mField_name).GetValue(item);

        if (currentTs - itemTs > timespan)
        {
          ex_count++;
          expiredList.Add(item);
        }
        else
          break;
      }
      timestamp_list.RemoveRange(0, ex_count);
      timestamp_list.Add(value);
      Seed = Accumulator(Seed, value, expiredList, timestamp_list.Count);
      subject.OnNext(Seed);
    }

    private List<T> timestamp_list;
    private Int64 timespan;
    private TAccumulate Seed;
    private Func<TAccumulate, T, IList<T>, long, TAccumulate> Accumulator;
    private string mField_name;
  };

  public static class QueryExtensions
  {
    public static IObservable<TAccumulate> TimeWindowForTsDataAggregate<T, TAccumulate> (
      this IObservable<T> source,
      Int64 timespan, string fieldName, TAccumulate seed, 
      Func<TAccumulate, T, IList<T>, long, TAccumulate> accumulator)
    {
      return new TimeWindowAggregatorForTsDataOp<T, TAccumulate>(source, timespan, fieldName, seed, accumulator);
    }
  }
}
