/*
 * Author: Kishore Reddy
 * Url: http://commonlibrarynet.codeplex.com/
 * Title: CommonLibrary.NET
 * Copyright: � 2009 Kishore Reddy
 * License: LGPL License
 * LicenseUrl: http://commonlibrarynet.codeplex.com/license
 * Description: A C# based .NET 3.5 Open-Source collection of reusable components.
 * Usage: Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
using System;
using System.Data;
using System.Collections.Generic;


namespace ComLib.Entities
{
    /// <summary>
    /// Persistant entity 
    /// </summary>
    public interface IEntityPersistant<TId>
    {
        /// <summary>
        /// Get the id of a persistant entity.
        /// </summary>
        TId Id { get; set; }


        /// <summary>
        /// Determines whether this instance is persistant.
        /// </summary>
        /// <returns>
        /// 	<c>true</c> if this instance is persistant; otherwise, <c>false</c>.
        /// </returns>
        bool IsPersistant();
    }



    /// <summary>
    /// Auditable entity.
    /// This interface is meant to provide auditing features to
    /// any entity/domain object.
    /// When changing the data model, at times it important to know.
    /// 1. who made a change.
    /// 2. when the change was made.
    /// 3. who created it.
    /// 4. what version it is.
    /// </summary>
    public interface IEntityAuditable
    {
        /// <summary>
        /// Date the entity was created.
        /// </summary>
        DateTime CreateDate { get; set; }


        /// <summary>
        /// User who first created this entity.
        /// </summary>
        string CreateUser { get; set; }


        /// <summary>
        /// Date the entitye was updated.
        /// </summary>
        DateTime UpdateDate { get; set; }


        /// <summary>
        /// User who last updated the entity.
        /// </summary>
        string UpdateUser { get; set; }


        /// <summary>
        /// Comment used for updates.
        /// </summary>
        string UpdateComment { get; set; }
    }



    /// <summary>
    /// Interface for versioned entities.
    /// </summary>
    public interface IEntityVersioned : IEntity
    {
        /// <summary>
        /// Version number.
        /// </summary>
        int Version { get; set; }


        /// <summary>
        /// Reference of the Id of the entity w/ the latest version.
        /// This used set for older entities to refer to the latest entity.
        /// </summary>
        int VersionRefId { get; set; }


        /// <summary>
        /// Whether or not this is the latest version.
        /// This can be achieved using a test for VersionRefId == -1.
        /// </summary>
        /// <returns></returns>
        bool IsLatestVersion();
    }



    /// <summary>
    /// Entity interface.
    /// </summary>
    public interface IEntity : IEntityPersistant<int>, IEntityAuditable, IEntityCallbacks, ICloneable
    {
        /// <summary>
        /// Determines if the entity is valid.
        /// </summary>
        bool IsValid { get; }

        /// <summary>
        /// Validate the entity and return collection of errors.
        /// </summary>
        /// <returns></returns>
        bool Validate();


        /// <summary>
        /// Validate the entity using the supplied result collection to collect errors.
        /// </summary>
        /// <param name="results"></param>
        /// <returns></returns>
        bool Validate(IValidationResults results);


        /// <summary>
        /// Validate this entity and collects/stores any validation errors
        /// into the results supplied and optionally copies the errors into the internal error state for this entity.
        /// </summary>
        /// <returns></returns>
        bool Validate(IValidationResults results, bool copyToInternalErrors);


        /// <summary>
        /// The the last validation result that is available.
        /// </summary>
        IValidationResults Errors { get; }        
    }



    /// <summary>
    /// Callbacks for the persistance lifecycle.
    /// </summary>
    public interface IEntityCallbacks
    {
        bool OnBeforeValidate(object ctx);
        bool OnBeforeValidateCreate(object ctx);
        bool OnBeforeValidateUpdate(object ctx);
        bool OnBeforeCreate(object ctx);
        bool OnBeforeUpdate(object ctx);
        bool OnBeforeSave(object ctx);
        bool OnBeforeDelete(object ctx);

        void OnAfterNew();
        void OnAfterValidate();
        void OnAfterValidateCreate();
        void OnAfterValidateUpdate();
        void OnAfterCreate();
        void OnAfterUpdate();
        void OnAfterSave();
        void OnAfterDelete();
    }
}
