﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComLib.Benchmarks
{
    /// <summary>
    /// Result for a benchmark run
    /// </summary>
    public class BenchmarkResult
    {
        /// <summary>
        /// Name of the benchmark run. 
        /// </summary>
        public string Name;


        /// <summary>
        /// Message supplied to bench mark run.
        /// </summary>
        public string Message;

        
        /// <summary>
        /// The date this benchmark was run on.
        /// </summary>
        public DateTime DateRun = DateTime.Today;


        /// <summary>
        /// The start time of the benchmark
        /// </summary>
        public TimeSpan TimeStarted;


        /// <summary>
        /// The end time of the benchmark.
        /// </summary>
        public TimeSpan TimeEnded;


        /// <summary>
        /// The difference in the start and end times.
        /// </summary>
        public TimeSpan TimeDiff;


        /// <summary>
        /// String representation of benchmark result.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return string.Format("Name:{0}, Message:{1}, Date:{2}, Started:{3}, Ended:{4}, Duration:{5}", 
                                  Name, Message, DateRun, TimeStarted.Milliseconds, TimeEnded.Milliseconds, TimeDiff.Milliseconds);

        }


        /// <summary>
        /// String representation of benchmark result.
        /// </summary>
        /// <returns></returns>
        public string ToStringXml()
        {
            return string.Format("<benchmarkresult name=\"{0}\" message=\"{1}\" date=\"{2}\" started=\"{3}\" ended=\"{4}\" duration=\"{5}\" />",
                                  Name, Message, DateRun, TimeStarted.Milliseconds, TimeEnded.Milliseconds, TimeDiff.Milliseconds);

        }


        /// <summary>
        /// String representation of benchmark result.
        /// </summary>
        /// <returns></returns>
        public string ToStringJson()
        {
            return string.Format("\"benchmarkresult\" : { name=\"{0}\", message=\"{1}\", date=\"{2}\", started=\"{3}\", ended=\"{4}\", duration=\"{5}\" }",
                                  Name, Message, DateRun, TimeStarted.Milliseconds, TimeEnded.Milliseconds, TimeDiff.Milliseconds);

        }
    }
}
