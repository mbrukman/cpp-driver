/*
  Copyright (c) 2014-2016 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef __CASS_LIST_POLICY_HPP_INCLUDED__
#define __CASS_LIST_POLICY_HPP_INCLUDED__

#include "load_balancing.hpp"
#include "host.hpp"
#include "scoped_ptr.hpp"

namespace cass {

class ListPolicy : public ChainedLoadBalancingPolicy {
public:
  ListPolicy(LoadBalancingPolicy* child_policy)
    : ChainedLoadBalancingPolicy(child_policy) {}

  virtual ~ListPolicy() {}

  virtual void init(const SharedRefPtr<Host>& connected_host, const HostMap& hosts, Random* random);

  virtual CassHostDistance distance(const SharedRefPtr<Host>& host) const;

  virtual QueryPlan* new_query_plan(const std::string& connected_keyspace,
                                    const Request* request,
                                    const TokenMap* token_map,
                                    Request::EncodingCache* cache);

  virtual void on_add(const SharedRefPtr<Host>& host);
  virtual void on_remove(const SharedRefPtr<Host>& host);
  virtual void on_up(const SharedRefPtr<Host>& host);
  virtual void on_down(const SharedRefPtr<Host>& host);

  virtual ListPolicy* new_instance() = 0;

private:
  virtual bool is_valid_host(const SharedRefPtr<Host>& host) const = 0;

};

} // namespace cass

#endif

