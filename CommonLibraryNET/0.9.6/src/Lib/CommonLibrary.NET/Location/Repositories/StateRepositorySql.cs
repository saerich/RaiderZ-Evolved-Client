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
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;

using ComLib.Entities;
using ComLib.Data;
using ComLib.LocationSupport;



namespace ComLib.LocationSupport
{
    /// <summary>
    /// Generic repository for persisting State.
    /// </summary>
    public partial class StateRepository : RepositorySql<State>
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NamedQueryRepository"/> class.
        /// </summary>
        public StateRepository() { }

        
        /// <summary>
        /// Initializes a new instance of the <see cref="Repository&lt;TId, T&gt;"/> class.
        /// </summary>
        /// <param name="connectionInfo">The connection string.</param>
        public  StateRepository(string connectionString) : base(connectionString)
        {
        }


        /// <summary>
        /// Initializes a new instance of the <see cref="Repository&lt;TId, T&gt;"/> class.
        /// </summary>
        /// <param name="connectionInfo">The connection info.</param>
        /// <param name="helper">The helper.</param>
        public StateRepository(ConnectionInfo connectionInfo) : base(connectionInfo)
        {            
        }


        /// <summary>
        /// Initializes a new instance of the <see cref="Repository&lt;TId, T&gt;"/> class.
        /// </summary>
        /// <param name="connectionInfo">The connection info.</param>
        /// <param name="helper">The helper.</param>
        public StateRepository(ConnectionInfo connectionInfo, IDatabase db)
            : base(connectionInfo, db)
        {
        }


        /// <summary>
        /// Initialize the rowmapper
        /// </summary>
        public override void Init(ConnectionInfo connectionInfo, IDatabase db)
        {
            base.Init(connectionInfo, db);
            this.RowMapper = new StateRowMapper();
        }


        /// <summary>
        /// Create the entity using sql.
        /// </summary>
        /// <param name="entity"></param>
        /// <returns></returns>
        public override State Create(State entity)
        {
            string sql = "insert into States ( [CreateDate], [UpdateDate], [CreateUser], [UpdateUser], [UpdateComment], [CountryId]"
			 + ", [CountryName], [Name], [Abbreviation], [AliasRefName], [IsActive], [IsAlias]"
			 + ", [AliasRefId] ) values ( @CreateDate, @UpdateDate, @CreateUser, @UpdateUser, @UpdateComment, @CountryId"
			 + ", @CountryName, @Name, @Abbreviation, @AliasRefName, @IsActive, @IsAlias"
			 + ", @AliasRefId );" + IdentityStatement;;
            var dbparams = BuildParams(entity);            
            object result = _db.ExecuteScalarText(sql, dbparams);
            entity.Id = Convert.ToInt32(result);
            return entity;
        }


        /// <summary>
        /// Update the entity using sql.
        /// </summary>
        /// <param name="entity"></param>
        /// <returns></returns>
        public override State Update(State entity)
        {
            string sql = "update States set [CreateDate] = @CreateDate, [UpdateDate] = @UpdateDate, [CreateUser] = @CreateUser, [UpdateUser] = @UpdateUser, [UpdateComment] = @UpdateComment, [CountryId] = @CountryId"
			 + ", [CountryName] = @CountryName, [Name] = @Name, [Abbreviation] = @Abbreviation, [AliasRefName] = @AliasRefName, [IsActive] = @IsActive, [IsAlias] = @IsAlias"
			 + ", [AliasRefId] = @AliasRefId where Id = " + entity.Id;
            var dbparams = BuildParams(entity); 
            _db.ExecuteNonQueryText(sql, dbparams);
            return entity;
        }


        public override State Get(int id)
        {
            State entity = base.Get(id);
            
            return entity;
        }


        protected virtual DbParameter[] BuildParams(State entity)
        {
            var dbparams = new List<DbParameter>();
            			dbparams.Add(BuildParam("@CreateDate", SqlDbType.DateTime, entity.CreateDate));
			dbparams.Add(BuildParam("@UpdateDate", SqlDbType.DateTime, entity.UpdateDate));
			dbparams.Add(BuildParam("@CreateUser", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.CreateUser) ? "" : entity.CreateUser));
			dbparams.Add(BuildParam("@UpdateUser", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.UpdateUser) ? "" : entity.UpdateUser));
			dbparams.Add(BuildParam("@UpdateComment", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.UpdateComment) ? "" : entity.UpdateComment));
			dbparams.Add(BuildParam("@CountryId", SqlDbType.Int, entity.CountryId));
			dbparams.Add(BuildParam("@CountryName", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.CountryName) ? "" : entity.CountryName));
			dbparams.Add(BuildParam("@Name", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.Name) ? "" : entity.Name));
			dbparams.Add(BuildParam("@Abbreviation", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.Abbreviation) ? "" : entity.Abbreviation));
			dbparams.Add(BuildParam("@AliasRefName", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.AliasRefName) ? "" : entity.AliasRefName));
			dbparams.Add(BuildParam("@IsActive", SqlDbType.Bit, entity.IsActive));
			dbparams.Add(BuildParam("@IsAlias", SqlDbType.Bit, entity.IsAlias));
			dbparams.Add(BuildParam("@AliasRefId", SqlDbType.Int, entity.AliasRefId));

            return dbparams.ToArray();
        }


        protected virtual DbParameter BuildParam(string name, SqlDbType dbType, object val)
        {
            var param = new SqlParameter(name, dbType);
            param.Value = val;
            return param;
        }

    }


    
    /// <summary>
    /// RowMapper for State.
    /// </summary>
    /// <typeparam name="?"></typeparam>
    public partial class StateRowMapper : EntityRowMapper<State>, IEntityRowMapper<State>
    {
        public override State MapRow(IDataReader reader, int rowNumber)
        {
            State entity =  _entityFactoryMethod == null ? new State() : _entityFactoryMethod(reader);
            			entity.Id = reader["Id"] == DBNull.Value ? 0 : (int)reader["Id"];
			entity.CreateDate = reader["CreateDate"] == DBNull.Value ? DateTime.MinValue : (DateTime)reader["CreateDate"];
			entity.UpdateDate = reader["UpdateDate"] == DBNull.Value ? DateTime.MinValue : (DateTime)reader["UpdateDate"];
			entity.CreateUser = reader["CreateUser"] == DBNull.Value ? string.Empty : reader["CreateUser"].ToString();
			entity.UpdateUser = reader["UpdateUser"] == DBNull.Value ? string.Empty : reader["UpdateUser"].ToString();
			entity.UpdateComment = reader["UpdateComment"] == DBNull.Value ? string.Empty : reader["UpdateComment"].ToString();
			entity.CountryId = reader["CountryId"] == DBNull.Value ? 0 : (int)reader["CountryId"];
			entity.CountryName = reader["CountryName"] == DBNull.Value ? string.Empty : reader["CountryName"].ToString();
			entity.Name = reader["Name"] == DBNull.Value ? string.Empty : reader["Name"].ToString();
			entity.Abbreviation = reader["Abbreviation"] == DBNull.Value ? string.Empty : reader["Abbreviation"].ToString();
			entity.AliasRefName = reader["AliasRefName"] == DBNull.Value ? string.Empty : reader["AliasRefName"].ToString();
			entity.IsActive = reader["IsActive"] == DBNull.Value ? false : (bool)reader["IsActive"];
			entity.IsAlias = reader["IsAlias"] == DBNull.Value ? false : (bool)reader["IsAlias"];
			entity.AliasRefId = reader["AliasRefId"] == DBNull.Value ? 0 : (int)reader["AliasRefId"];

            return entity;
        }
    }
}