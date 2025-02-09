﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data;
using System.Data.Common;

using ComLib;
using ComLib.Application;
using ComLib.Logging;
using ComLib.Authentication;
using ComLib.Environments;
using ComLib.BootStrapSupport;


namespace ComLib.Samples
{
    /// <summary>
    /// Example of ActiveRecord Initialization/Configuration.
    /// </summary>
    public class Example_BootStrapper : App
    {
        private BootStrapper _bootup;


        /// <summary>
        /// Create a bootstrapper
        /// </summary>
        /// <param name="context"></param>
        public override void Init(object context)
        {
            base.Init(context);
            _bootup = new BootStrapper();
        } 


        /// <summary>
        /// Run the application.
        /// </summary>
        public override BoolMessageItem Execute()
        {
            // Example 1:  Non-Fluent API to configure Bootup services on startup.
            //
            // 1. Put into group called "core", parameter "core"
            // 2. With Importance as High. parameter "Importance.High"
            // 3. They must succeed without exception or the entire bootup fails. parameter "false"
            _bootup.OnStart("Authentication", "core", BootTask.Importance.High, false, (ctx) => Auth.Init(new AuthWin()));
            _bootup.OnStart("Environment",    "core", BootTask.Importance.High, false, (ctx) => Env.Change("qa"));
            _bootup.OnStart("Logging Support", "core", BootTask.Importance.High, false, (ctx) => Console.WriteLine("Logging setup in call base.Init(context);"));
            

            // Example 2: Fluent API to configure bootup services on startup.
            //
            // 1. put into group called "myapp".
            // 2. Various levels of importance.            
            _bootup.OnStart(BootTask.Named("Themes").InGroup("app").PriorityHigh.MustSucceed().ActionIs((ctx)     => Console.WriteLine("Themes setup")));
            _bootup.OnStart(BootTask.Named("Widgets").InGroup("app").PriorityHigh.MustSucceed().ActionIs((ctx)    => Console.WriteLine("Widgets setup")));
            _bootup.OnStart(BootTask.Named("Profiles").InGroup("app").PriorityNormal.CanFail().ActionIs((ctx)     => Console.WriteLine("Profiles setup")));
            _bootup.OnStart(BootTask.Named("MVC Areas").InGroup("mvc").PriorityHigh.MustSucceed().ActionIs((ctx)  => Console.WriteLine("MVC Areas setup")));
            _bootup.OnStart(BootTask.Named("MVC Routes").InGroup("mvc").PriorityHigh.MustSucceed().ActionIs((ctx) => Console.WriteLine("MVC Routes setup")));
            
            // Example 3: Run all Startup services.
            _bootup.StartUp(new AppContext());
           
            // Example 4: Run only selected startup services.
            _bootup.StartUp(new AppContext(), new string[] { "Environment", "Logging Support" });

            // Example 5: Get status info for all the tasks and write to console.
            _bootup.GetStartupStatus().ForEach(task =>
                        Console.WriteLine(string.Format("Task Name: {0}, Group: {1}, Passed: {2}, Importance: {3}, Time: {4}",
                                                          task.Name, task.Group, task.Success, task.Priority.ToString(), task.ExecutedOn.ToShortTimeString())));

            return BoolMessageItem.True;
        }      
    }
}
