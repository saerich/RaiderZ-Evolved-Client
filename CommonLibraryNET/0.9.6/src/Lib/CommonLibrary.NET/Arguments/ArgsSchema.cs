﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComLib.Arguments
{
    /// <summary>
    /// Schema used for arguments.
    /// </summary>
    public class ArgsSchema
    {
        private Args _args;
        private List<ArgAttribute> _attributes = new List<ArgAttribute>();
        private ArgAttribute _last;


        /// <summary>
        /// Initialize with the args object.
        /// </summary>
        /// <param name="args"></param>
        public ArgsSchema(Args args) : this( args, null)
        {            
        }


        /// <summary>
        /// Initialize with the args object a list of arg attributes.
        /// </summary>
        /// <param name="args"></param>
        /// <param name="argAttributes"></param>
        public ArgsSchema(Args args, List<ArgAttribute> argAttributes)
        {
            _args = args;
            if( argAttributes != null) 
                _attributes = argAttributes;
        }


        /// <summary>
        /// The args object.
        /// </summary>
        public Args Args
        {
            get { return _args; }
        }


        /// <summary>
        /// Should make this readonly or copy it
        /// </summary>
        public List<ArgAttribute> Items
        {
            get { return _attributes; }
            set { _attributes = value; }
        }


        /// <summary>
        /// Indicate whether or not there are any options in this schema.
        /// </summary>
        public bool IsEmpty
        {
            get { return _attributes == null || _attributes.Count == 0; }
        }


        /// <summary>
        /// The number of options.
        /// </summary>
        public int Count
        {
            get { return _attributes.Count; }
        }


        /// <summary>
        /// Add a named argument using it's name and whether it's required, default value and description.
        /// </summary>
        /// <typeparam name="T">The type of argument.</typeparam>
        /// <param name="name">Name of the argument.</param>
        /// <param name="alias">Short hand name for the argument.</param>
        /// <param name="isRequired">Whether or not this argument is required.</param>
        /// <param name="defaultValue">Default value to use if it's not supplied.</param>
        /// <param name="description">Description of this argument.</param>
        /// <param name="example">An example value for the argument.</param>
        /// <param name="exampleMultiple">Multiple examples for the argument</param>
        /// <param name="interpret">Whether or the argument value should be interpreted to handle things like ${t} for DateTime.Today</param>
        /// <param name="isCaseSensitive">Whether or the argument name is case-sensitive</param>
        /// <param name="tag">A tag to associate w/ the argument.</param>
        /// <param name="onlyForDevelopment">Whether or not the argument is only for development purposes</param>
        /// <returns></returns>
        public ArgsSchema AddNamed<T>(string name, string alias = "", bool isRequired = false, T defaultValue = default(T), string description = "",
            string example = "", string exampleMultiple = "", bool interpret = false, bool isCaseSensitive = false, string tag = "", bool onlyForDevelopment = false)
        {
            return Add<T>(-1, name, alias, isRequired, defaultValue, description, example, exampleMultiple, interpret, isCaseSensitive, tag, onlyForDevelopment);
        }


        /// <summary>
        /// Add a positional argument.
        /// </summary>
        /// <typeparam name="T">The type of the argument.</typeparam>
        /// <param name="indexPosition">Index</param>
        /// <param name="isRequired">Whether or not this argument is required.</param>
        /// <param name="defaultValue">Default value to use if it's not supplied.</param>
        /// <param name="description">Description of this argument.</param>
        /// <param name="example">An example value for the argument.</param>
        /// <param name="exampleMultiple">Multiple examples for the argument</param>
        /// <param name="interpret">Whether or the argument value should be interpreted to handle things like ${t} for DateTime.Today</param>
        /// <param name="isCaseSensitive">Whether or the argument name is case-sensitive</param>
        /// <param name="tag">A tag to associate w/ the argument.</param>
        /// <param name="onlyForDevelopment">Whether or not the argument is only for development purposes</param>
        /// <returns></returns>
        public ArgsSchema AddPositional<T>(int indexPosition, bool isRequired = false, T defaultValue = default(T), string description = "",
            string example = "", string exampleMultiple = "", bool interpret = false, bool isCaseSensitive = false, string tag = "", bool onlyForDevelopment = false)
        {
            return Add<T>(indexPosition, string.Empty, string.Empty, isRequired, defaultValue, description, example, exampleMultiple, interpret, isCaseSensitive, tag, onlyForDevelopment);
        }


        private ArgsSchema Add<T>(int indexPosition, string name, string alias, bool isRequired, T defaultValue, string description, string example, string exampleMultipe, bool interpret,
           bool isCaseSensitive, string tag, bool onlyForDevelopment)
        {
            var latest = new ArgAttribute()
            {
                Name = name,
                Alias = alias,
                DefaultValue = defaultValue,
                Description = description,
                DataType = typeof(T),
                Example = example,
                ExampleMultiple = exampleMultipe,
                Interpret = interpret,
                IsCaseSensitive = isCaseSensitive,
                IsRequired = isRequired,
                IsUsedOnlyForDevelopment = onlyForDevelopment,
                Tag = tag
            };
            _attributes.Add(latest);
            _last = latest;

            return this;
        }


        /// <summary>
        /// Remove the argument with the supplied name.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public ArgsSchema RemoveNamed(string name)
        {
            var arg = (from a in _attributes where string.Equals(a.Name, name) select a).First<ArgAttribute>();
            _attributes.Remove(arg);
            return this;
        }


        /// <summary>
        /// Remove the positional argument at the supplied index.
        /// </summary>
        /// <param name="indexPosition"></param>
        /// <returns></returns>
        public ArgsSchema RemovPositional(int indexPosition)
        {
            var arg = (from a in _attributes where a.IndexPosition.Equals(indexPosition) select a).First<ArgAttribute>();
            _attributes.Remove(arg);
            return this;
        }


        /// <summary>
        /// Clear all the arguments in this schema.
        /// </summary>
        /// <returns></returns>
        public ArgsSchema Clear()
        {
            _attributes.Clear();
            return this;
        }


        /// <summary>
        /// Whether or not the schema contains an argument with the supplied name.
        /// </summary>
        /// <param name="argName"></param>
        /// <returns></returns>
        public bool Contains(string argName)
        {
            var arg = (from a in _attributes where string.Equals(a.Name, argName) select a).First<ArgAttribute>();
            return arg != null;
        }


        /// <summary>
        /// Whether or not the schema contains a positional argument at the supplied index.
        /// </summary>
        /// <param name="indexPosition"></param>
        /// <returns></returns>
        public bool Contains(int indexPosition)
        {
            var arg = (from a in _attributes where a.IndexPosition.Equals(indexPosition) select a).First<ArgAttribute>();
            return arg != null;
        }


        /// <summary>
        /// Mark the current argument as required.
        /// </summary>
        public ArgsSchema Required
        {
            get { return SetLastArgProperty(arg => arg.IsRequired = true); }
        }


        /// <summary>
        /// Mark the current argument as optional.
        /// </summary>
        public ArgsSchema Optional
        {
            get { return SetLastArgProperty(arg => arg.IsRequired = false); }
        }


        /// <summary>
        /// Set the description for the current argument as optional.
        /// </summary>
        public ArgsSchema Describe(string description)
        {
            return SetLastArgProperty(arg => arg.Description = description);
        }


        /// <summary>
        /// Set the default value for the current argument.
        /// </summary>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public ArgsSchema DefaultsTo(object defaultValue)
        {
            return SetLastArgProperty(arg => arg.DefaultValue = defaultValue);
        }


        /// <summary>
        /// Mark the current argument as being used only for development purposes
        /// </summary>
        public ArgsSchema OnlyForDevelopment
        {
            get { return SetLastArgProperty(arg => arg.IsUsedOnlyForDevelopment = true); }
        }


        /// <summary>
        /// Mark the current argument as Case Sensitive
        /// </summary>
        public ArgsSchema CaseSensitive
        {
            get { return SetLastArgProperty(arg => arg.IsCaseSensitive = true); }
        }        


        /// <summary>
        /// Mark the current argument as Case Insensitive
        /// </summary>
        public ArgsSchema CaseInSensitive
        {
            get { return SetLastArgProperty(arg => arg.IsCaseSensitive = false); }
        }


        /// <summary>
        /// Specify examples for the current argument.
        /// </summary>
        /// <param name="singleExample"></param>
        /// <param name="multipleExamples"></param>
        /// <returns></returns>
        public ArgsSchema Examples(string singleExample, string multipleExamples)
        {
            return SetLastArgProperty(arg => { arg.Example = singleExample; arg.ExampleMultiple = multipleExamples; });
        }
        

        /// <summary>
        /// Mark current argument as interpretable.
        /// </summary>
        public ArgsSchema Interpret
        {
            get { return SetLastArgProperty(arg => arg.Interpret = true); }
        }


        private ArgsSchema SetLastArgProperty(Action<ArgAttribute> action)
        {
            action(_last);
            return this;
        }
    }
}
