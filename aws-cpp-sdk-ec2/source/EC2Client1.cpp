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
#include <aws/core/utils/Outcome.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/EC2Endpoint.h>
#include <aws/ec2/EC2ErrorMarshaller.h>
#include <aws/ec2/model/AcceptVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/AllocateAddressRequest.h>
#include <aws/ec2/model/AllocateHostsRequest.h>
#include <aws/ec2/model/AssignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/AssociateAddressRequest.h>
#include <aws/ec2/model/AssociateDhcpOptionsRequest.h>
#include <aws/ec2/model/AssociateRouteTableRequest.h>
#include <aws/ec2/model/AttachClassicLinkVpcRequest.h>
#include <aws/ec2/model/AttachInternetGatewayRequest.h>
#include <aws/ec2/model/AttachNetworkInterfaceRequest.h>
#include <aws/ec2/model/AttachVolumeRequest.h>
#include <aws/ec2/model/AttachVpnGatewayRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/BundleInstanceRequest.h>
#include <aws/ec2/model/CancelBundleTaskRequest.h>
#include <aws/ec2/model/CancelConversionTaskRequest.h>
#include <aws/ec2/model/CancelExportTaskRequest.h>
#include <aws/ec2/model/CancelImportTaskRequest.h>
#include <aws/ec2/model/CancelReservedInstancesListingRequest.h>
#include <aws/ec2/model/CancelSpotFleetRequestsRequest.h>
#include <aws/ec2/model/CancelSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/ConfirmProductInstanceRequest.h>
#include <aws/ec2/model/CopyImageRequest.h>
#include <aws/ec2/model/CopySnapshotRequest.h>
#include <aws/ec2/model/CreateCustomerGatewayRequest.h>
#include <aws/ec2/model/CreateDhcpOptionsRequest.h>
#include <aws/ec2/model/CreateFlowLogsRequest.h>
#include <aws/ec2/model/CreateImageRequest.h>
#include <aws/ec2/model/CreateInstanceExportTaskRequest.h>
#include <aws/ec2/model/CreateInternetGatewayRequest.h>
#include <aws/ec2/model/CreateKeyPairRequest.h>
#include <aws/ec2/model/CreateNatGatewayRequest.h>
#include <aws/ec2/model/CreateNetworkAclRequest.h>
#include <aws/ec2/model/CreateNetworkAclEntryRequest.h>
#include <aws/ec2/model/CreateNetworkInterfaceRequest.h>
#include <aws/ec2/model/CreatePlacementGroupRequest.h>
#include <aws/ec2/model/CreateReservedInstancesListingRequest.h>
#include <aws/ec2/model/CreateRouteRequest.h>
#include <aws/ec2/model/CreateRouteTableRequest.h>
#include <aws/ec2/model/CreateSecurityGroupRequest.h>
#include <aws/ec2/model/CreateSnapshotRequest.h>
#include <aws/ec2/model/CreateSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/CreateSubnetRequest.h>
#include <aws/ec2/model/CreateTagsRequest.h>
#include <aws/ec2/model/CreateVolumeRequest.h>
#include <aws/ec2/model/CreateVpcRequest.h>
#include <aws/ec2/model/CreateVpcEndpointRequest.h>
#include <aws/ec2/model/CreateVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRouteRequest.h>
#include <aws/ec2/model/CreateVpnGatewayRequest.h>
#include <aws/ec2/model/DeleteCustomerGatewayRequest.h>
#include <aws/ec2/model/DeleteDhcpOptionsRequest.h>
#include <aws/ec2/model/DeleteFlowLogsRequest.h>
#include <aws/ec2/model/DeleteInternetGatewayRequest.h>
#include <aws/ec2/model/DeleteKeyPairRequest.h>
#include <aws/ec2/model/DeleteNatGatewayRequest.h>
#include <aws/ec2/model/DeleteNetworkAclRequest.h>
#include <aws/ec2/model/DeleteNetworkAclEntryRequest.h>
#include <aws/ec2/model/DeleteNetworkInterfaceRequest.h>
#include <aws/ec2/model/DeletePlacementGroupRequest.h>
#include <aws/ec2/model/DeleteRouteRequest.h>
#include <aws/ec2/model/DeleteRouteTableRequest.h>
#include <aws/ec2/model/DeleteSecurityGroupRequest.h>
#include <aws/ec2/model/DeleteSnapshotRequest.h>
#include <aws/ec2/model/DeleteSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DeleteSubnetRequest.h>
#include <aws/ec2/model/DeleteTagsRequest.h>
#include <aws/ec2/model/DeleteVolumeRequest.h>
#include <aws/ec2/model/DeleteVpcRequest.h>
#include <aws/ec2/model/DeleteVpcEndpointsRequest.h>
#include <aws/ec2/model/DeleteVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRouteRequest.h>
#include <aws/ec2/model/DeleteVpnGatewayRequest.h>
#include <aws/ec2/model/DeregisterImageRequest.h>
#include <aws/ec2/model/DescribeAccountAttributesRequest.h>
#include <aws/ec2/model/DescribeAddressesRequest.h>
#include <aws/ec2/model/DescribeAvailabilityZonesRequest.h>
#include <aws/ec2/model/DescribeBundleTasksRequest.h>
#include <aws/ec2/model/DescribeClassicLinkInstancesRequest.h>
#include <aws/ec2/model/DescribeConversionTasksRequest.h>
#include <aws/ec2/model/DescribeCustomerGatewaysRequest.h>
#include <aws/ec2/model/DescribeDhcpOptionsRequest.h>
#include <aws/ec2/model/DescribeExportTasksRequest.h>
#include <aws/ec2/model/DescribeFlowLogsRequest.h>
#include <aws/ec2/model/DescribeHostsRequest.h>
#include <aws/ec2/model/DescribeIdFormatRequest.h>
#include <aws/ec2/model/DescribeImageAttributeRequest.h>
#include <aws/ec2/model/DescribeImagesRequest.h>
#include <aws/ec2/model/DescribeImportImageTasksRequest.h>
#include <aws/ec2/model/DescribeImportSnapshotTasksRequest.h>
#include <aws/ec2/model/DescribeInstanceAttributeRequest.h>
#include <aws/ec2/model/DescribeInstanceStatusRequest.h>
#include <aws/ec2/model/DescribeInstancesRequest.h>
#include <aws/ec2/model/DescribeInternetGatewaysRequest.h>
#include <aws/ec2/model/DescribeKeyPairsRequest.h>
#include <aws/ec2/model/DescribeMovingAddressesRequest.h>
#include <aws/ec2/model/DescribeNatGatewaysRequest.h>
#include <aws/ec2/model/DescribeNetworkAclsRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfacesRequest.h>
#include <aws/ec2/model/DescribePlacementGroupsRequest.h>
#include <aws/ec2/model/DescribePrefixListsRequest.h>
#include <aws/ec2/model/DescribeRegionsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesListingsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesModificationsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesOfferingsRequest.h>
#include <aws/ec2/model/DescribeRouteTablesRequest.h>
#include <aws/ec2/model/DescribeScheduledInstanceAvailabilityRequest.h>
#include <aws/ec2/model/DescribeScheduledInstancesRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupsRequest.h>
#include <aws/ec2/model/DescribeSnapshotAttributeRequest.h>
#include <aws/ec2/model/DescribeSnapshotsRequest.h>
#include <aws/ec2/model/DescribeSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DescribeSpotFleetInstancesRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestHistoryRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotPriceHistoryRequest.h>
#include <aws/ec2/model/DescribeSubnetsRequest.h>
#include <aws/ec2/model/DescribeTagsRequest.h>
#include <aws/ec2/model/DescribeVolumeAttributeRequest.h>
#include <aws/ec2/model/DescribeVolumeStatusRequest.h>
#include <aws/ec2/model/DescribeVolumesRequest.h>
#include <aws/ec2/model/DescribeVpcAttributeRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointServicesRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointsRequest.h>
#include <aws/ec2/model/DescribeVpcPeeringConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpcsRequest.h>
#include <aws/ec2/model/DescribeVpnConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpnGatewaysRequest.h>
#include <aws/ec2/model/DetachClassicLinkVpcRequest.h>
#include <aws/ec2/model/DetachInternetGatewayRequest.h>
#include <aws/ec2/model/DetachNetworkInterfaceRequest.h>
#include <aws/ec2/model/DetachVolumeRequest.h>
#include <aws/ec2/model/DetachVpnGatewayRequest.h>
#include <aws/ec2/model/DisableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DisassociateAddressRequest.h>
#include <aws/ec2/model/DisassociateRouteTableRequest.h>
#include <aws/ec2/model/EnableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/EnableVolumeIORequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkRequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/GetConsoleOutputRequest.h>
#include <aws/ec2/model/GetPasswordDataRequest.h>
#include <aws/ec2/model/ImportImageRequest.h>
#include <aws/ec2/model/ImportInstanceRequest.h>
#include <aws/ec2/model/ImportKeyPairRequest.h>
#include <aws/ec2/model/ImportSnapshotRequest.h>
#include <aws/ec2/model/ImportVolumeRequest.h>
#include <aws/ec2/model/ModifyHostsRequest.h>
#include <aws/ec2/model/ModifyIdFormatRequest.h>
#include <aws/ec2/model/ModifyImageAttributeRequest.h>
#include <aws/ec2/model/ModifyInstanceAttributeRequest.h>
#include <aws/ec2/model/ModifyInstancePlacementRequest.h>
#include <aws/ec2/model/ModifyNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ModifyReservedInstancesRequest.h>
#include <aws/ec2/model/ModifySnapshotAttributeRequest.h>
#include <aws/ec2/model/ModifySpotFleetRequestRequest.h>
#include <aws/ec2/model/ModifySubnetAttributeRequest.h>
#include <aws/ec2/model/ModifyVolumeAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointRequest.h>
#include <aws/ec2/model/MonitorInstancesRequest.h>
#include <aws/ec2/model/MoveAddressToVpcRequest.h>
#include <aws/ec2/model/PurchaseReservedInstancesOfferingRequest.h>
#include <aws/ec2/model/PurchaseScheduledInstancesRequest.h>
#include <aws/ec2/model/RebootInstancesRequest.h>
#include <aws/ec2/model/RegisterImageRequest.h>
#include <aws/ec2/model/RejectVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/ReleaseAddressRequest.h>
#include <aws/ec2/model/ReleaseHostsRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclAssociationRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclEntryRequest.h>
#include <aws/ec2/model/ReplaceRouteRequest.h>
#include <aws/ec2/model/ReplaceRouteTableAssociationRequest.h>
#include <aws/ec2/model/ReportInstanceStatusRequest.h>
#include <aws/ec2/model/RequestSpotFleetRequest.h>
#include <aws/ec2/model/RequestSpotInstancesRequest.h>
#include <aws/ec2/model/ResetImageAttributeRequest.h>
#include <aws/ec2/model/ResetInstanceAttributeRequest.h>
#include <aws/ec2/model/ResetNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ResetSnapshotAttributeRequest.h>
#include <aws/ec2/model/RestoreAddressToClassicRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/RunInstancesRequest.h>
#include <aws/ec2/model/RunScheduledInstancesRequest.h>
#include <aws/ec2/model/StartInstancesRequest.h>
#include <aws/ec2/model/StopInstancesRequest.h>
#include <aws/ec2/model/TerminateInstancesRequest.h>
#include <aws/ec2/model/UnassignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/UnmonitorInstancesRequest.h>

using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::EC2;
using namespace Aws::EC2::Model;
using namespace Aws::Http;
using namespace Aws::Utils::Xml;


static const char* SERVICE_NAME = "ec2";
static const char* ALLOCATION_TAG = "EC2Client";

EC2Client::EC2Client(const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(Aws::MakeShared<HttpClientFactory>(ALLOCATION_TAG), clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<DefaultAWSCredentialsProviderChain>(ALLOCATION_TAG),
        SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region) : clientConfiguration.authenticationRegion),
    Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::EC2Client(const AWSCredentials& credentials, const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(Aws::MakeShared<HttpClientFactory>(ALLOCATION_TAG), clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<SimpleAWSCredentialsProvider>(ALLOCATION_TAG, credentials),
         SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region) : clientConfiguration.authenticationRegion),
    Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::EC2Client(const std::shared_ptr<AWSCredentialsProvider>& credentialsProvider,
  const Client::ClientConfiguration& clientConfiguration, const std::shared_ptr<HttpClientFactory const>& httpClientFactory) :
  BASECLASS(httpClientFactory != nullptr ? httpClientFactory : Aws::MakeShared<HttpClientFactory>(ALLOCATION_TAG), clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, credentialsProvider,
         SERVICE_NAME, clientConfiguration.authenticationRegion.empty() ? RegionMapper::GetRegionName(clientConfiguration.region) : clientConfiguration.authenticationRegion),
    Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::~EC2Client()
{
}

void EC2Client::init(const ClientConfiguration& config)
{
  Aws::StringStream ss;
  ss << SchemeMapper::ToString(config.scheme) << "://";

  if(config.endpointOverride.empty() && config.authenticationRegion.empty())
  {
    ss << EC2Endpoint::ForRegion(config.region);
  }
  else
  {
    ss << config.endpointOverride;
  }

  m_uri = ss.str();
}
AcceptVpcPeeringConnectionOutcome EC2Client::AcceptVpcPeeringConnection(const AcceptVpcPeeringConnectionRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AcceptVpcPeeringConnectionOutcome(AcceptVpcPeeringConnectionResponse(outcome.GetResult()));
  }
  else
  {
    return AcceptVpcPeeringConnectionOutcome(outcome.GetError());
  }
}

AcceptVpcPeeringConnectionOutcomeCallable EC2Client::AcceptVpcPeeringConnectionCallable(const AcceptVpcPeeringConnectionRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AcceptVpcPeeringConnection, this, request);
}

void EC2Client::AcceptVpcPeeringConnectionAsync(const AcceptVpcPeeringConnectionRequest& request, const AcceptVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AcceptVpcPeeringConnectionAsyncHelper, this, request, handler, context);
}

void EC2Client::AcceptVpcPeeringConnectionAsyncHelper(const AcceptVpcPeeringConnectionRequest& request, const AcceptVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AcceptVpcPeeringConnection(request), context);
}

AllocateAddressOutcome EC2Client::AllocateAddress(const AllocateAddressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AllocateAddressOutcome(AllocateAddressResponse(outcome.GetResult()));
  }
  else
  {
    return AllocateAddressOutcome(outcome.GetError());
  }
}

AllocateAddressOutcomeCallable EC2Client::AllocateAddressCallable(const AllocateAddressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AllocateAddress, this, request);
}

void EC2Client::AllocateAddressAsync(const AllocateAddressRequest& request, const AllocateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AllocateAddressAsyncHelper, this, request, handler, context);
}

void EC2Client::AllocateAddressAsyncHelper(const AllocateAddressRequest& request, const AllocateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AllocateAddress(request), context);
}

AllocateHostsOutcome EC2Client::AllocateHosts(const AllocateHostsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AllocateHostsOutcome(AllocateHostsResponse(outcome.GetResult()));
  }
  else
  {
    return AllocateHostsOutcome(outcome.GetError());
  }
}

AllocateHostsOutcomeCallable EC2Client::AllocateHostsCallable(const AllocateHostsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AllocateHosts, this, request);
}

void EC2Client::AllocateHostsAsync(const AllocateHostsRequest& request, const AllocateHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AllocateHostsAsyncHelper, this, request, handler, context);
}

void EC2Client::AllocateHostsAsyncHelper(const AllocateHostsRequest& request, const AllocateHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AllocateHosts(request), context);
}

AssignPrivateIpAddressesOutcome EC2Client::AssignPrivateIpAddresses(const AssignPrivateIpAddressesRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AssignPrivateIpAddressesOutcome(NoResult());
  }
  else
  {
    return AssignPrivateIpAddressesOutcome(outcome.GetError());
  }
}

AssignPrivateIpAddressesOutcomeCallable EC2Client::AssignPrivateIpAddressesCallable(const AssignPrivateIpAddressesRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AssignPrivateIpAddresses, this, request);
}

void EC2Client::AssignPrivateIpAddressesAsync(const AssignPrivateIpAddressesRequest& request, const AssignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AssignPrivateIpAddressesAsyncHelper, this, request, handler, context);
}

void EC2Client::AssignPrivateIpAddressesAsyncHelper(const AssignPrivateIpAddressesRequest& request, const AssignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AssignPrivateIpAddresses(request), context);
}

AssociateAddressOutcome EC2Client::AssociateAddress(const AssociateAddressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AssociateAddressOutcome(AssociateAddressResponse(outcome.GetResult()));
  }
  else
  {
    return AssociateAddressOutcome(outcome.GetError());
  }
}

AssociateAddressOutcomeCallable EC2Client::AssociateAddressCallable(const AssociateAddressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AssociateAddress, this, request);
}

void EC2Client::AssociateAddressAsync(const AssociateAddressRequest& request, const AssociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AssociateAddressAsyncHelper, this, request, handler, context);
}

void EC2Client::AssociateAddressAsyncHelper(const AssociateAddressRequest& request, const AssociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AssociateAddress(request), context);
}

AssociateDhcpOptionsOutcome EC2Client::AssociateDhcpOptions(const AssociateDhcpOptionsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AssociateDhcpOptionsOutcome(NoResult());
  }
  else
  {
    return AssociateDhcpOptionsOutcome(outcome.GetError());
  }
}

AssociateDhcpOptionsOutcomeCallable EC2Client::AssociateDhcpOptionsCallable(const AssociateDhcpOptionsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AssociateDhcpOptions, this, request);
}

void EC2Client::AssociateDhcpOptionsAsync(const AssociateDhcpOptionsRequest& request, const AssociateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AssociateDhcpOptionsAsyncHelper, this, request, handler, context);
}

void EC2Client::AssociateDhcpOptionsAsyncHelper(const AssociateDhcpOptionsRequest& request, const AssociateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AssociateDhcpOptions(request), context);
}

AssociateRouteTableOutcome EC2Client::AssociateRouteTable(const AssociateRouteTableRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AssociateRouteTableOutcome(AssociateRouteTableResponse(outcome.GetResult()));
  }
  else
  {
    return AssociateRouteTableOutcome(outcome.GetError());
  }
}

AssociateRouteTableOutcomeCallable EC2Client::AssociateRouteTableCallable(const AssociateRouteTableRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AssociateRouteTable, this, request);
}

void EC2Client::AssociateRouteTableAsync(const AssociateRouteTableRequest& request, const AssociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AssociateRouteTableAsyncHelper, this, request, handler, context);
}

void EC2Client::AssociateRouteTableAsyncHelper(const AssociateRouteTableRequest& request, const AssociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AssociateRouteTable(request), context);
}

AttachClassicLinkVpcOutcome EC2Client::AttachClassicLinkVpc(const AttachClassicLinkVpcRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AttachClassicLinkVpcOutcome(AttachClassicLinkVpcResponse(outcome.GetResult()));
  }
  else
  {
    return AttachClassicLinkVpcOutcome(outcome.GetError());
  }
}

AttachClassicLinkVpcOutcomeCallable EC2Client::AttachClassicLinkVpcCallable(const AttachClassicLinkVpcRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AttachClassicLinkVpc, this, request);
}

void EC2Client::AttachClassicLinkVpcAsync(const AttachClassicLinkVpcRequest& request, const AttachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AttachClassicLinkVpcAsyncHelper, this, request, handler, context);
}

void EC2Client::AttachClassicLinkVpcAsyncHelper(const AttachClassicLinkVpcRequest& request, const AttachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AttachClassicLinkVpc(request), context);
}

AttachInternetGatewayOutcome EC2Client::AttachInternetGateway(const AttachInternetGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AttachInternetGatewayOutcome(NoResult());
  }
  else
  {
    return AttachInternetGatewayOutcome(outcome.GetError());
  }
}

AttachInternetGatewayOutcomeCallable EC2Client::AttachInternetGatewayCallable(const AttachInternetGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AttachInternetGateway, this, request);
}

void EC2Client::AttachInternetGatewayAsync(const AttachInternetGatewayRequest& request, const AttachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AttachInternetGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::AttachInternetGatewayAsyncHelper(const AttachInternetGatewayRequest& request, const AttachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AttachInternetGateway(request), context);
}

AttachNetworkInterfaceOutcome EC2Client::AttachNetworkInterface(const AttachNetworkInterfaceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AttachNetworkInterfaceOutcome(AttachNetworkInterfaceResponse(outcome.GetResult()));
  }
  else
  {
    return AttachNetworkInterfaceOutcome(outcome.GetError());
  }
}

AttachNetworkInterfaceOutcomeCallable EC2Client::AttachNetworkInterfaceCallable(const AttachNetworkInterfaceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AttachNetworkInterface, this, request);
}

void EC2Client::AttachNetworkInterfaceAsync(const AttachNetworkInterfaceRequest& request, const AttachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AttachNetworkInterfaceAsyncHelper, this, request, handler, context);
}

void EC2Client::AttachNetworkInterfaceAsyncHelper(const AttachNetworkInterfaceRequest& request, const AttachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AttachNetworkInterface(request), context);
}

AttachVolumeOutcome EC2Client::AttachVolume(const AttachVolumeRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AttachVolumeOutcome(AttachVolumeResponse(outcome.GetResult()));
  }
  else
  {
    return AttachVolumeOutcome(outcome.GetError());
  }
}

AttachVolumeOutcomeCallable EC2Client::AttachVolumeCallable(const AttachVolumeRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AttachVolume, this, request);
}

void EC2Client::AttachVolumeAsync(const AttachVolumeRequest& request, const AttachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AttachVolumeAsyncHelper, this, request, handler, context);
}

void EC2Client::AttachVolumeAsyncHelper(const AttachVolumeRequest& request, const AttachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AttachVolume(request), context);
}

AttachVpnGatewayOutcome EC2Client::AttachVpnGateway(const AttachVpnGatewayRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AttachVpnGatewayOutcome(AttachVpnGatewayResponse(outcome.GetResult()));
  }
  else
  {
    return AttachVpnGatewayOutcome(outcome.GetError());
  }
}

AttachVpnGatewayOutcomeCallable EC2Client::AttachVpnGatewayCallable(const AttachVpnGatewayRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AttachVpnGateway, this, request);
}

void EC2Client::AttachVpnGatewayAsync(const AttachVpnGatewayRequest& request, const AttachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AttachVpnGatewayAsyncHelper, this, request, handler, context);
}

void EC2Client::AttachVpnGatewayAsyncHelper(const AttachVpnGatewayRequest& request, const AttachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AttachVpnGateway(request), context);
}

AuthorizeSecurityGroupEgressOutcome EC2Client::AuthorizeSecurityGroupEgress(const AuthorizeSecurityGroupEgressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AuthorizeSecurityGroupEgressOutcome(NoResult());
  }
  else
  {
    return AuthorizeSecurityGroupEgressOutcome(outcome.GetError());
  }
}

AuthorizeSecurityGroupEgressOutcomeCallable EC2Client::AuthorizeSecurityGroupEgressCallable(const AuthorizeSecurityGroupEgressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AuthorizeSecurityGroupEgress, this, request);
}

void EC2Client::AuthorizeSecurityGroupEgressAsync(const AuthorizeSecurityGroupEgressRequest& request, const AuthorizeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AuthorizeSecurityGroupEgressAsyncHelper, this, request, handler, context);
}

void EC2Client::AuthorizeSecurityGroupEgressAsyncHelper(const AuthorizeSecurityGroupEgressRequest& request, const AuthorizeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AuthorizeSecurityGroupEgress(request), context);
}

AuthorizeSecurityGroupIngressOutcome EC2Client::AuthorizeSecurityGroupIngress(const AuthorizeSecurityGroupIngressRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return AuthorizeSecurityGroupIngressOutcome(NoResult());
  }
  else
  {
    return AuthorizeSecurityGroupIngressOutcome(outcome.GetError());
  }
}

AuthorizeSecurityGroupIngressOutcomeCallable EC2Client::AuthorizeSecurityGroupIngressCallable(const AuthorizeSecurityGroupIngressRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::AuthorizeSecurityGroupIngress, this, request);
}

void EC2Client::AuthorizeSecurityGroupIngressAsync(const AuthorizeSecurityGroupIngressRequest& request, const AuthorizeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::AuthorizeSecurityGroupIngressAsyncHelper, this, request, handler, context);
}

void EC2Client::AuthorizeSecurityGroupIngressAsyncHelper(const AuthorizeSecurityGroupIngressRequest& request, const AuthorizeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, AuthorizeSecurityGroupIngress(request), context);
}

BundleInstanceOutcome EC2Client::BundleInstance(const BundleInstanceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return BundleInstanceOutcome(BundleInstanceResponse(outcome.GetResult()));
  }
  else
  {
    return BundleInstanceOutcome(outcome.GetError());
  }
}

BundleInstanceOutcomeCallable EC2Client::BundleInstanceCallable(const BundleInstanceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::BundleInstance, this, request);
}

void EC2Client::BundleInstanceAsync(const BundleInstanceRequest& request, const BundleInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::BundleInstanceAsyncHelper, this, request, handler, context);
}

void EC2Client::BundleInstanceAsyncHelper(const BundleInstanceRequest& request, const BundleInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, BundleInstance(request), context);
}

CancelBundleTaskOutcome EC2Client::CancelBundleTask(const CancelBundleTaskRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelBundleTaskOutcome(CancelBundleTaskResponse(outcome.GetResult()));
  }
  else
  {
    return CancelBundleTaskOutcome(outcome.GetError());
  }
}

CancelBundleTaskOutcomeCallable EC2Client::CancelBundleTaskCallable(const CancelBundleTaskRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelBundleTask, this, request);
}

void EC2Client::CancelBundleTaskAsync(const CancelBundleTaskRequest& request, const CancelBundleTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelBundleTaskAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelBundleTaskAsyncHelper(const CancelBundleTaskRequest& request, const CancelBundleTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelBundleTask(request), context);
}

CancelConversionTaskOutcome EC2Client::CancelConversionTask(const CancelConversionTaskRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelConversionTaskOutcome(NoResult());
  }
  else
  {
    return CancelConversionTaskOutcome(outcome.GetError());
  }
}

CancelConversionTaskOutcomeCallable EC2Client::CancelConversionTaskCallable(const CancelConversionTaskRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelConversionTask, this, request);
}

void EC2Client::CancelConversionTaskAsync(const CancelConversionTaskRequest& request, const CancelConversionTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelConversionTaskAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelConversionTaskAsyncHelper(const CancelConversionTaskRequest& request, const CancelConversionTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelConversionTask(request), context);
}

CancelExportTaskOutcome EC2Client::CancelExportTask(const CancelExportTaskRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelExportTaskOutcome(NoResult());
  }
  else
  {
    return CancelExportTaskOutcome(outcome.GetError());
  }
}

CancelExportTaskOutcomeCallable EC2Client::CancelExportTaskCallable(const CancelExportTaskRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelExportTask, this, request);
}

void EC2Client::CancelExportTaskAsync(const CancelExportTaskRequest& request, const CancelExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelExportTaskAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelExportTaskAsyncHelper(const CancelExportTaskRequest& request, const CancelExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelExportTask(request), context);
}

CancelImportTaskOutcome EC2Client::CancelImportTask(const CancelImportTaskRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelImportTaskOutcome(CancelImportTaskResponse(outcome.GetResult()));
  }
  else
  {
    return CancelImportTaskOutcome(outcome.GetError());
  }
}

CancelImportTaskOutcomeCallable EC2Client::CancelImportTaskCallable(const CancelImportTaskRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelImportTask, this, request);
}

void EC2Client::CancelImportTaskAsync(const CancelImportTaskRequest& request, const CancelImportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelImportTaskAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelImportTaskAsyncHelper(const CancelImportTaskRequest& request, const CancelImportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelImportTask(request), context);
}

CancelReservedInstancesListingOutcome EC2Client::CancelReservedInstancesListing(const CancelReservedInstancesListingRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelReservedInstancesListingOutcome(CancelReservedInstancesListingResponse(outcome.GetResult()));
  }
  else
  {
    return CancelReservedInstancesListingOutcome(outcome.GetError());
  }
}

CancelReservedInstancesListingOutcomeCallable EC2Client::CancelReservedInstancesListingCallable(const CancelReservedInstancesListingRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelReservedInstancesListing, this, request);
}

void EC2Client::CancelReservedInstancesListingAsync(const CancelReservedInstancesListingRequest& request, const CancelReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelReservedInstancesListingAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelReservedInstancesListingAsyncHelper(const CancelReservedInstancesListingRequest& request, const CancelReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelReservedInstancesListing(request), context);
}

CancelSpotFleetRequestsOutcome EC2Client::CancelSpotFleetRequests(const CancelSpotFleetRequestsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelSpotFleetRequestsOutcome(CancelSpotFleetRequestsResponse(outcome.GetResult()));
  }
  else
  {
    return CancelSpotFleetRequestsOutcome(outcome.GetError());
  }
}

CancelSpotFleetRequestsOutcomeCallable EC2Client::CancelSpotFleetRequestsCallable(const CancelSpotFleetRequestsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelSpotFleetRequests, this, request);
}

void EC2Client::CancelSpotFleetRequestsAsync(const CancelSpotFleetRequestsRequest& request, const CancelSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelSpotFleetRequestsAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelSpotFleetRequestsAsyncHelper(const CancelSpotFleetRequestsRequest& request, const CancelSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelSpotFleetRequests(request), context);
}

CancelSpotInstanceRequestsOutcome EC2Client::CancelSpotInstanceRequests(const CancelSpotInstanceRequestsRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CancelSpotInstanceRequestsOutcome(CancelSpotInstanceRequestsResponse(outcome.GetResult()));
  }
  else
  {
    return CancelSpotInstanceRequestsOutcome(outcome.GetError());
  }
}

CancelSpotInstanceRequestsOutcomeCallable EC2Client::CancelSpotInstanceRequestsCallable(const CancelSpotInstanceRequestsRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::CancelSpotInstanceRequests, this, request);
}

void EC2Client::CancelSpotInstanceRequestsAsync(const CancelSpotInstanceRequestsRequest& request, const CancelSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::CancelSpotInstanceRequestsAsyncHelper, this, request, handler, context);
}

void EC2Client::CancelSpotInstanceRequestsAsyncHelper(const CancelSpotInstanceRequestsRequest& request, const CancelSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CancelSpotInstanceRequests(request), context);
}

ConfirmProductInstanceOutcome EC2Client::ConfirmProductInstance(const ConfirmProductInstanceRequest& request) const
{
  Aws::StringStream ss;
  ss << m_uri << "/";
  XmlOutcome outcome = MakeRequest(ss.str(), request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ConfirmProductInstanceOutcome(ConfirmProductInstanceResponse(outcome.GetResult()));
  }
  else
  {
    return ConfirmProductInstanceOutcome(outcome.GetError());
  }
}

ConfirmProductInstanceOutcomeCallable EC2Client::ConfirmProductInstanceCallable(const ConfirmProductInstanceRequest& request) const
{
  return std::async(std::launch::async, &EC2Client::ConfirmProductInstance, this, request);
}

void EC2Client::ConfirmProductInstanceAsync(const ConfirmProductInstanceRequest& request, const ConfirmProductInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit(&EC2Client::ConfirmProductInstanceAsyncHelper, this, request, handler, context);
}

void EC2Client::ConfirmProductInstanceAsyncHelper(const ConfirmProductInstanceRequest& request, const ConfirmProductInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, ConfirmProductInstance(request), context);
}

