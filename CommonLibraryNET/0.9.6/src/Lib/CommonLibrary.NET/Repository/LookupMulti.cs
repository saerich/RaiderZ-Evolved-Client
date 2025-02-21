﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Collections;
using System.Text;
using System.Data;
using System.Data.Common;
using System.Linq.Expressions;


using ComLib;
using ComLib.Data;
using ComLib.Entities;


namespace ComLib.Entities
{

    /// <summary>
    /// Interface for looking up data by id or name.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public interface ILookUpMulti<T>
    {
        T this[int id] { get; }
        T this[string name] { get; }
    }


    
    /// <summary>
    /// Used to lookup items by both an int and string.
    /// This is useful when looking up item by Id and Name for example.
    /// This is the case for some entities such as City/Country.
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class LookupMulti<T>
    {
        /// <summary>
        /// Lookup by ids
        /// </summary>
        protected IDictionary<int, T> _itemsById1;


        /// <summary>
        /// Lookup by names.
        /// </summary>
        protected IDictionary<string, T> _itemsById2;


        /// <summary>
        /// Default initialization.
        /// </summary>
        public LookupMulti() { }


        /// <summary>
        /// Initialize w/ lamdas for getting the ids, names.
        /// </summary>
        /// <param name="items"></param>
        /// <param name="idGetter"></param>
        /// <param name="strIdGetter"></param>
        public LookupMulti(IList<T> items, Func<T, int> idGetter, Func<T, string> strIdGetter)
        {
            Init(items, null, idGetter, strIdGetter, null);
        }


        /// <summary>
        /// Initialzie using lamdas for getting the ids and names.
        /// </summary>
        /// <param name="items"></param>
        /// <param name="predicate"></param>
        /// <param name="idGetter"></param>
        /// <param name="strIdGetter"></param>
        public LookupMulti(IList<T> items, Func<T, bool> predicate, Func<T, int> idGetter, Func<T, string> strIdGetter)
        {
            Init(items, predicate, idGetter, strIdGetter, null);
        }


        /// <summary>
        /// Initialize with supplied data.
        /// </summary>
        /// <param name="itemsById">Map of ids to items</param>
        /// <param name="itemsByName">Map of names to items</param>
        public LookupMulti(IDictionary<int, T> itemsById, IDictionary<string, T> itemsByName)
        {
            _itemsById1 = itemsById;
            _itemsById2 = itemsByName;
        }


        /// <summary>
        /// Get the first lookup.
        /// </summary>
        public IDictionary<int, T> Lookup1 { get { return _itemsById1; } }


        /// <summary>
        /// Get the second lookup
        /// </summary>
        public IDictionary<string, T> Lookup2 { get { return _itemsById2; } }


        /// <summary>
        /// Returns the location item given the id.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public virtual T this[int id]
        {
            get 
            {
                // Check.
                if (!_itemsById1.ContainsKey(id))
                    return default(T);

                return _itemsById1[id]; 
            }
        }


        /// <summary>
        /// Contains the key.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public bool ContainsKey(int id)
        {
            return _itemsById1.ContainsKey(id);
        }


        /// <summary>
        /// Flag to indicate if the key is there.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public bool ContainsKey(string id)
        {
            return _itemsById2.ContainsKey(id);
        }
        

        /// <summary>
        /// Returns the location item given the full name ("New York") or abbr ( "NY" )
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public virtual T this[string id]
        {
            get 
            {
                if (string.IsNullOrEmpty(id))
                    return default(T);

                if (_itemsById2.ContainsKey(id))
                    return _itemsById2[id];

                id = id.Trim().ToLower();

                // Check.
                if (!_itemsById2.ContainsKey(id))
                    return default(T);

                return _itemsById2[id]; 
            }
        }

        
        /// <summary>
        /// Initialize the lookups by using the 2 id values associated w/ the property names supplied.
        /// </summary>
        /// <param name="items">The items to store.</param>
        /// <param name="predicate">The condition to check to see if it's ok to add a specific item.</param>
        /// <param name="id1Getter">The lamda to get the int id.</param>
        /// <param name="strId2Getter">The lamda to get the strin id.</param>
        /// <param name="callback">Callback to notify calle that item has been added.</param>
        public virtual void Init(IList<T> items, Func<T, bool> predicate, Func<T, int> id1Getter, Func<T,string> strId2Getter, Action<T, int, string> callback)
        {
            _itemsById1 = new Dictionary<int, T>();
            _itemsById2 = new Dictionary<string, T>();

            items.ForEach(item =>
            {
                bool okToAdd = predicate == null ? true : predicate(item);

                if (okToAdd)
                {
                    int id1 = id1Getter(item);
                    string id2 = strId2Getter == null ? string.Empty : strId2Getter(item);

                    _itemsById1[id1] = item;
                    if (!string.IsNullOrEmpty(id2)) _itemsById2[id2] = item;

                    if (callback != null)
                        callback(item, id1, id2);
                }
            });
        }
    }
}
