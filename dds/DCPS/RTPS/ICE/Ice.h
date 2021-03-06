/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef OPENDDS_RTPS_ICE_H
#define OPENDDS_RTPS_ICE_H

#include "dds/DCPS/ICE/Ice.h"
#include "dds/DCPS/RTPS/ICE/Stun.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL

namespace OpenDDS {
namespace ICE {

typedef OPENDDS_VECTOR(ACE_INET_Addr) AddressListType;

class OpenDDS_Rtps_Export Endpoint {
public:
  virtual ~Endpoint() {}
  virtual AddressListType host_addresses() const = 0;
  virtual void send(const ACE_INET_Addr& address, const STUN::Message& message) = 0;
  virtual ACE_INET_Addr stun_server_address() const = 0;
};

class OpenDDS_Rtps_Export AgentInfoListener {
public:
  virtual ~AgentInfoListener() {}
  virtual void update_agent_info(const DCPS::RepoId& a_local_guid,
                                 const AgentInfo& a_agent_info) = 0;
};

class OpenDDS_Rtps_Export Configuration {
public:
  Configuration() :
    T_a_(0, 50000),
    connectivity_check_ttl_(5 * 60),
    checklist_period_(10),
    indication_period_(15),
    nominated_ttl_(5 * 60),
    server_reflexive_address_period_(30),
    server_reflexive_indication_count_(10),
    deferred_triggered_check_ttl_(5 * 60),
    change_password_period_(5 * 60)
  {}

  void T_a(const ACE_Time_Value& x)
  {
    T_a_ = x;
  }
  ACE_Time_Value T_a() const
  {
    return T_a_;
  }

  void connectivity_check_ttl(const ACE_Time_Value& x)
  {
    connectivity_check_ttl_ = x;
  }
  ACE_Time_Value connectivity_check_ttl() const
  {
    return connectivity_check_ttl_;
  }

  void checklist_period(const ACE_Time_Value& x)
  {
    checklist_period_ = x;
  }
  ACE_Time_Value checklist_period() const
  {
    return checklist_period_;
  }

  void indication_period(const ACE_Time_Value& x)
  {
    indication_period_ = x;
  }
  ACE_Time_Value indication_period() const
  {
    return indication_period_;
  }

  void nominated_ttl(const ACE_Time_Value& x)
  {
    nominated_ttl_ = x;
  }
  ACE_Time_Value nominated_ttl() const
  {
    return nominated_ttl_;
  }

  void server_reflexive_address_period(const ACE_Time_Value& x)
  {
    server_reflexive_address_period_ = x;
  }
  ACE_Time_Value server_reflexive_address_period() const
  {
    return server_reflexive_address_period_;
  }

  void server_reflexive_indication_count(size_t x)
  {
    server_reflexive_indication_count_ = x;
  }
  size_t server_reflexive_indication_count() const
  {
    return server_reflexive_indication_count_;
  }

  void deferred_triggered_check_ttl(const ACE_Time_Value& x)
  {
    deferred_triggered_check_ttl_ = x;
  }
  ACE_Time_Value deferred_triggered_check_ttl() const
  {
    return deferred_triggered_check_ttl_;
  }

  void change_password_period(const ACE_Time_Value& x)
  {
    change_password_period_ = x;
  }
  ACE_Time_Value change_password_period() const
  {
    return change_password_period_;
  }

private:
  // Mininum time between consecutive sends.
  // RFC 8445 Section 14.2
  ACE_Time_Value T_a_;
  // Repeat a check for this long before failing it.
  ACE_Time_Value connectivity_check_ttl_;
  // Run all of the ordinary checks in a checklist in this amount of time.
  ACE_Time_Value checklist_period_;
  // Send an indication at this interval once an address is selected.
  ACE_Time_Value indication_period_;
  // The nominated pair will still be valid if an indication has been received within this amount of time.
  ACE_Time_Value nominated_ttl_;
  // Perform server-reflexive candidate gathering this often.
  ACE_Time_Value server_reflexive_address_period_;
  // Send this many binding indications to the STUN server before sending a binding request.
  size_t server_reflexive_indication_count_;
  // Lifetime of a deferred triggered check.
  ACE_Time_Value deferred_triggered_check_ttl_;
  // Change the password this often.
  ACE_Time_Value change_password_period_;
};

class OpenDDS_Rtps_Export Agent {
public:
  virtual ~Agent() {}
  virtual Configuration& get_configuration() = 0;
  virtual void add_endpoint(Endpoint* a_endpoint) = 0;
  virtual void remove_endpoint(Endpoint* a_endpoint) = 0;
  virtual AgentInfo get_local_agent_info(Endpoint* a_endpoint) const = 0;
  virtual void add_local_agent_info_listener(Endpoint* a_endpoint,
                                             const DCPS::RepoId& a_local_guid,
                                             AgentInfoListener* a_agent_info_listener) = 0;
  virtual void remove_local_agent_info_listener(Endpoint* a_endpoint,
                                                const DCPS::RepoId& a_local_guid) = 0;
  virtual void start_ice(Endpoint* a_endpoint,
                         const DCPS::RepoId& a_local_guid,
                         const DCPS::RepoId& a_remote_guid,
                         const AgentInfo& a_remote_agent_info) = 0;
  virtual void stop_ice(Endpoint* a_endpoint,
                        const DCPS::RepoId& a_local_guid,
                        const DCPS::RepoId& a_remote_guid) = 0;
  virtual ACE_INET_Addr get_address(Endpoint* a_endpoint,
                                    const DCPS::RepoId& a_local_guid,
                                    const DCPS::RepoId& a_remote_guid) const = 0;

  // Receive a STUN message.
  virtual void receive(Endpoint* a_endpoint,
                       const ACE_INET_Addr& a_local_address,
                       const ACE_INET_Addr& a_remote_address,
                       const STUN::Message& a_message) = 0;

  static Agent* instance();
};

std::ostream& operator<<(std::ostream& stream, const ACE_INET_Addr& address);
std::ostream& operator<<(std::ostream& stream, const STUN::TransactionId& tid);
std::ostream& operator<<(std::ostream& stream, const ICE::Candidate& candidate);
std::ostream& operator<<(std::ostream& stream, const ICE::AgentInfo& agent_info);

} // namespace ICE
} // namespace OpenDDS

OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_RTPS_ICE_H */
