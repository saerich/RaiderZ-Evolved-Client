/*
 * Author: Justin Dial
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
using System.Collections.Generic;
using System.Data.Linq.Mapping;
using System.Data.Common;
using System.Data;
using System.Data.SqlClient;
using ComLib.Entities;
using ComLib.Data;


namespace ComLib.Logging
{
    /// <summary>
    /// Making the LogEventEntity implement IEntity.
    /// 
    /// Reasons:
    /// 1. Takes advantage of outof the box DomainModel functionality.
    /// 2. Can now use RepositoryLinq2Sql as the repository for CRUD actions.
    /// 
    /// </summary>
    public class LogEventEntity : ActiveRecordBaseEntity<LogEventEntity>, IEntity
    {
        /// <summary>
        /// Creates a new instance of BlogPost and 
        /// initializes it with a validator and settings.
        /// </summary>
        /// <returns></returns>
        public static LogEventEntity New()
        {
            LogEventEntity entity = new LogEventEntity();
            return entity;
        }  


        /// <summary>
        /// Get/Set Application
        /// </summary>
        public string Application { get; set; }


        /// <summary>
        /// Get/Set Computer
        /// </summary>
        public string Computer { get; set; }


        /// <summary>
        /// Get/Set LogLevel
        /// </summary>
        public int LogLevel { get; set; }


        /// <summary>
        /// Get/Set Exception
        /// </summary>
        public string Exception { get; set; }


        /// <summary>
        /// Get/Set Message
        /// </summary>
        public string Message { get; set; }


        /// <summary>
        /// Get/Set UserName
        /// </summary>
        public string UserName { get; set; }


        #region Static Helper Methods
        /// <summary>
        /// Delete all entries based on the level.
        /// </summary>
        /// <param name="level"></param>
        public static void Delete(LogLevel level)
        {
            var logService = EntityRegistration.GetService<LogEventEntity>();
            logService.Repository.Delete(Query<LogEventEntity>.New().Where( l => l.LogLevel).Is((int)level));
            //entity => entity.LogLevel == level);
        }


        /// <summary>
        /// Delete log entries before the specified date.
        /// </summary>
        /// <param name="date"></param>
        /// /// <returns></returns>
        public static void Delete(DateTime date, bool beforeDate)
        {
            IRepository<LogEventEntity> repo = EntityRegistration.GetRepository<LogEventEntity>();
            if (beforeDate)
                repo.Delete(entity => entity.CreateDate < date);
            else
                repo.Delete(entity => entity.CreateDate > date);
        }
        #endregion


        /// <summary>
        /// Get the name of the log level.
        /// </summary>
        public string LogLevelName
        {
            get
            {
                LogLevel level = (LogLevel)Enum.Parse(typeof(LogLevel), LogLevel.ToString());
                return level.ToString();
            }
        }

    }



    /// <summary>
    /// Creates a LogEventEntity from the contents of a LogEvent
    /// </summary>
    public class LogEventEntityMapper : IMapper<LogEvent, LogEventEntity>
    {
        /// <summary>
        /// Map from the log event to the logevententity for persistance.
        /// </summary>
        /// <param name="mapFrom"></param>
        /// <returns></returns>
        public LogEventEntity MapFrom(LogEvent mapFrom)
        {
            LogEventEntity entity = new LogEventEntity();
            entity.UserName = mapFrom.UserName;
            entity.Computer = mapFrom.Computer;
            entity.Exception = mapFrom.Ex == null ? "" : mapFrom.Ex.Message;
            entity.Message = mapFrom.Message == null ? "" : mapFrom.Message.ToString();
            entity.LogLevel = (int)mapFrom.Level;
            entity.CreateDate = mapFrom.CreateTime;
            entity.UpdateDate = mapFrom.CreateTime;
            return entity;
        }
    }



    /// <summary>
    /// Lightweight input/output mapping interface
    /// </summary>
    /// <typeparam name="T">The type to be mapped from</typeparam>
    /// <typeparam name="TK">The type to be mapped to</typeparam>
    public interface IMapper<T, TK>
    {
        TK MapFrom(T mapFrom);
    } 



    /// <summary>
    /// Generic repository for persisting Log.
    /// </summary>
    public partial class LogRepository : RepositorySql<LogEventEntity>
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LogRepository"/> class.
        /// </summary>
        public LogRepository() { }


        /// <summary>
        /// Initializes a new instance of the <see cref="LogRepository"/> class.
        /// </summary>
        /// <param name="connectionString">The connection string.</param>
        public LogRepository(string connectionString)
            : base(connectionString)
        {
        }


        /// <summary>
        /// Initializes a new instance of the <see cref="LogRepository"/> class.
        /// </summary>
        /// <param name="connectionInfo">The connection info.</param>
        public LogRepository(ConnectionInfo connectionInfo)
            : base(connectionInfo)
        {
        }


        /// <summary>
        /// Initializes a new instance of the <see cref="LogRepository"/> class.
        /// </summary>
        /// <param name="connectionInfo">The connection info.</param>
        /// <param name="db">The database helper.</param>
        public LogRepository(ConnectionInfo connectionInfo, IDatabase db)
            : base(connectionInfo, db)
        {
        }


        /// <summary>
        /// Initialize the rowmapper
        /// </summary>
        public override void Init(ConnectionInfo connectionInfo, IDatabase db)
        {
            base.Init(connectionInfo, db);
            this.RowMapper = new LogEventEntityRowMapper();
        }


        /// <summary>
        /// Create the entity using sql.
        /// </summary>
        /// <param name="entity"></param>
        /// <returns></returns>
        public override LogEventEntity Create(LogEventEntity entity)
        {
            string sql = "insert into Logs ( [CreateDate], [UpdateDate], [CreateUser], [UpdateUser], [UpdateComment], [Application]"
             + ", [Computer], [LogLevel], [Exception], [Message], [UserName] ) values ( @CreateDate, @UpdateDate, @CreateUser, @UpdateUser, @UpdateComment, @Application"
             + ", @Computer, @LogLevel, @Exception, @Message, @UserName );" + IdentityStatement; ;
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
        public override LogEventEntity Update(LogEventEntity entity)
        {
            string sql = "update Logs set [CreateDate] = @CreateDate, [UpdateDate] = @UpdateDate, [CreateUser] = @CreateUser, [UpdateUser] = @UpdateUser, [UpdateComment] = @UpdateComment, [Application] = @Application"
             + ", [Computer] = @Computer, [LogLevel] = @LogLevel, [Exception] = @Exception, [Message] = @Message, [UserName] = @UserName where Id = " + entity.Id;
            var dbparams = BuildParams(entity);
            _db.ExecuteNonQueryText(sql, dbparams);
            return entity;
        }


        public override LogEventEntity Get(int id)
        {
            LogEventEntity entity = base.Get(id);

            return entity;
        }


        protected virtual DbParameter[] BuildParams(LogEventEntity entity)
        {
            var dbparams = new List<DbParameter>();
            dbparams.Add(BuildParam("@CreateDate", SqlDbType.DateTime, entity.CreateDate));
            dbparams.Add(BuildParam("@UpdateDate", SqlDbType.DateTime, entity.UpdateDate));
            dbparams.Add(BuildParam("@CreateUser", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.CreateUser) ? "" : entity.CreateUser));
            dbparams.Add(BuildParam("@UpdateUser", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.UpdateUser) ? "" : entity.UpdateUser));
            dbparams.Add(BuildParam("@UpdateComment", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.UpdateComment) ? "" : entity.UpdateComment));
            dbparams.Add(BuildParam("@Application", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.Application) ? "" : entity.Application));
            dbparams.Add(BuildParam("@Computer", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.Computer) ? "" : entity.Computer));
            dbparams.Add(BuildParam("@LogLevel", SqlDbType.Int, entity.LogLevel));
            dbparams.Add(BuildParam("@Exception", SqlDbType.NText, string.IsNullOrEmpty(entity.Exception) ? "" : entity.Exception));
            dbparams.Add(BuildParam("@Message", SqlDbType.NText, string.IsNullOrEmpty(entity.Message) ? "" : entity.Message));
            dbparams.Add(BuildParam("@UserName", SqlDbType.NVarChar, string.IsNullOrEmpty(entity.UserName) ? "" : entity.UserName));

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
    /// RowMapper for Log.
    /// </summary>
    /// <typeparam name="?"></typeparam>
    public partial class LogEventEntityRowMapper : EntityRowMapper<LogEventEntity>, IEntityRowMapper<LogEventEntity>
    {
        public override LogEventEntity MapRow(IDataReader reader, int rowNumber)
        {
            LogEventEntity entity = LogEventEntity.New();
            entity.Id = reader["Id"] == DBNull.Value ? 0 : (int)reader["Id"];
            entity.CreateDate = reader["CreateDate"] == DBNull.Value ? DateTime.MinValue : (DateTime)reader["CreateDate"];
            entity.UpdateDate = reader["UpdateDate"] == DBNull.Value ? DateTime.MinValue : (DateTime)reader["UpdateDate"];
            entity.CreateUser = reader["CreateUser"] == DBNull.Value ? string.Empty : reader["CreateUser"].ToString();
            entity.UpdateUser = reader["UpdateUser"] == DBNull.Value ? string.Empty : reader["UpdateUser"].ToString();
            entity.UpdateComment = reader["UpdateComment"] == DBNull.Value ? string.Empty : reader["UpdateComment"].ToString();
            entity.Application = reader["Application"] == DBNull.Value ? string.Empty : reader["Application"].ToString();
            entity.Computer = reader["Computer"] == DBNull.Value ? string.Empty : reader["Computer"].ToString();
            entity.LogLevel = reader["LogLevel"] == DBNull.Value ? 0 : (int)reader["LogLevel"];
            entity.Exception = reader["Exception"] == DBNull.Value ? string.Empty : reader["Exception"].ToString();
            entity.Message = reader["Message"] == DBNull.Value ? string.Empty : reader["Message"].ToString();
            entity.UserName = reader["UserName"] == DBNull.Value ? string.Empty : reader["UserName"].ToString();

            return entity;
        }
    }
}