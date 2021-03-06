/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#pragma once
#include <aws/apigateway/APIGateway_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/apigateway/model/ApiKey.h>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace APIGateway
{
namespace Model
{
  /**
   * <p>Represents a collection of <a>ApiKey</a> resources.</p>
   */
  class AWS_APIGATEWAY_API GetApiKeysResult
  {
  public:
    GetApiKeysResult();
    GetApiKeysResult(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    GetApiKeysResult& operator=(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);

    
    inline const Aws::String& GetPosition() const{ return m_position; }

    
    inline void SetPosition(const Aws::String& value) { m_position = value; }

    
    inline void SetPosition(Aws::String&& value) { m_position = value; }

    
    inline void SetPosition(const char* value) { m_position.assign(value); }

    
    inline GetApiKeysResult& WithPosition(const Aws::String& value) { SetPosition(value); return *this;}

    
    inline GetApiKeysResult& WithPosition(Aws::String&& value) { SetPosition(value); return *this;}

    
    inline GetApiKeysResult& WithPosition(const char* value) { SetPosition(value); return *this;}

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline const Aws::Vector<ApiKey>& GetItems() const{ return m_items; }

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline void SetItems(const Aws::Vector<ApiKey>& value) { m_items = value; }

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline void SetItems(Aws::Vector<ApiKey>&& value) { m_items = value; }

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline GetApiKeysResult& WithItems(const Aws::Vector<ApiKey>& value) { SetItems(value); return *this;}

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline GetApiKeysResult& WithItems(Aws::Vector<ApiKey>&& value) { SetItems(value); return *this;}

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline GetApiKeysResult& AddItems(const ApiKey& value) { m_items.push_back(value); return *this; }

    /**
     * <p>The current page of any <a>ApiKey</a> resources in the collection of
     * <a>ApiKey</a> resources.</p>
     */
    inline GetApiKeysResult& AddItems(ApiKey&& value) { m_items.push_back(value); return *this; }

  private:
    Aws::String m_position;
    Aws::Vector<ApiKey> m_items;
  };

} // namespace Model
} // namespace APIGateway
} // namespace Aws
