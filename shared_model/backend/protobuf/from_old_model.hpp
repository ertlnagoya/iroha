/**
 * Copyright Soramitsu Co., Ltd. 2018 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SHARED_MODEL_FROM_OLD_HPP
#define SHARED_MODEL_FROM_OLD_HPP
#ifndef DISABLE_BACKWARD

#include "backend/protobuf/block.hpp"
#include "backend/protobuf/proposal.hpp"
#include "backend/protobuf/queries/proto_query.hpp"
#include "backend/protobuf/transaction.hpp"
#include "model/converters/pb_block_factory.hpp"
#include "model/converters/pb_query_factory.hpp"
#include "model/converters/pb_transaction_factory.hpp"

namespace shared_model {
  namespace proto {

    inline static shared_model::proto::Block from_old(
        const iroha::model::Block &block) {
      return shared_model::proto::Block(
          iroha::model::converters::PbBlockFactory().serialize(block));
    }

    inline static shared_model::proto::Transaction from_old(
        const iroha::model::Transaction &tx) {
      return shared_model::proto::Transaction(
          iroha::model::converters::PbTransactionFactory().serialize(tx));
    }

    inline static shared_model::proto::Query from_old(
        const iroha::model::Query &qry) {
      return shared_model::proto::Query(
          *iroha::model::converters::PbQueryFactory().serialize(
              std::make_shared<iroha::model::Query>(qry)));
    }

    inline static shared_model::proto::Proposal from_old(
        const iroha::model::Proposal &proposal) {
      iroha::protocol::Proposal proto;
      proto.set_height(proposal.height);
      for (const auto &tx : proposal.transactions) {
        new (proto.add_transactions()) iroha::protocol::Transaction(
            iroha::model::converters::PbTransactionFactory().serialize(tx));
      }
      return shared_model::proto::Proposal(proto);
    }

  }  // namespace proto
}  // namespace shared_model

#endif  // DISABLE_BACKWARD
#endif  // SHARED_MODEL_FROM_OLD_HPP
