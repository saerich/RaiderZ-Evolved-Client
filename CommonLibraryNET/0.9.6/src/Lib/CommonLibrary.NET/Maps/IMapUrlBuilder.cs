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
using System.Globalization;
using System.Text;
using System.Xml;

using ComLib.LocationSupport;


namespace ComLib.Maps
{
    /// <summary>
    /// Interface for building an url to link to a mapping system.
    /// e.g. Url to access location on google or yahoo maps.
    /// </summary>
    public interface IMapUrlBuilder
    {
        string UrlPrefix { get; set; }
        string Build(Address address);
    }
}
