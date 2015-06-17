/*
* Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#include <aws/rds/model/DescribeDBLogFilesResult.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/AmazonWebServiceResult.h>
#include <aws/core/utils/StringUtils.h>

#include <utility>

using namespace Aws::RDS::Model;
using namespace Aws::Utils::Xml;
using namespace Aws::Utils;
using namespace Aws;

DescribeDBLogFilesResult::DescribeDBLogFilesResult()
{
}

DescribeDBLogFilesResult::DescribeDBLogFilesResult(const AmazonWebServiceResult<XmlDocument>& result)
{
  *this = result;
}

DescribeDBLogFilesResult& DescribeDBLogFilesResult::operator =(const AmazonWebServiceResult<XmlDocument>& result)
{
  const XmlDocument& xmlDocument = result.GetPayload();
  XmlNode rootNode = xmlDocument.GetRootElement();
  XmlNode resultNode = rootNode.FirstChild("DescribeDBLogFilesResult");

  if(!resultNode.IsNull())
  {
    XmlNode describeDBLogFilesDetailsNodeParent = resultNode.FirstChild("DescribeDBLogFilesDetails");
    XmlNode describeDBLogFilesDetailsNode = describeDBLogFilesDetailsNodeParent.FirstChild("member");
    while(!describeDBLogFilesDetailsNode.IsNull())
    {
      m_describeDBLogFiles.push_back(describeDBLogFilesDetailsNode);
      describeDBLogFilesDetailsNode = describeDBLogFilesDetailsNode.NextNode("member");
    }

    XmlNode markerNode = resultNode.FirstChild("Marker");
    m_marker = StringUtils::Trim(markerNode.GetText().c_str());
  }

  XmlNode responseMetadataNode = rootNode.FirstChild("ResponseMetadata");
  m_responseMetadata = responseMetadataNode;

  return *this;
}