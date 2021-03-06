/*
 * Copyright (c) 2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Elements/Payload.h>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

#include <Swiften/Elements/PubSubAffiliation.h>
#include <Swiften/Elements/PubSubPayload.h>

namespace Swift {
	class SWIFTEN_API PubSubAffiliations : public PubSubPayload {
		public:
			
			PubSubAffiliations();
			
			virtual ~PubSubAffiliations();

			const boost::optional< std::string >& getNode() const {
				return node;
			}

			void setNode(const boost::optional< std::string >& value) {
				this->node = value ;
			}

			const std::vector< boost::shared_ptr<PubSubAffiliation> >& getAffiliations() const {
				return affiliations;
			}

			void setAffiliations(const std::vector< boost::shared_ptr<PubSubAffiliation> >& value) {
				this->affiliations = value ;
			}

			void addAffiliation(boost::shared_ptr<PubSubAffiliation> value) {
				this->affiliations.push_back(value);
			}


		private:
			boost::optional< std::string > node;
			std::vector< boost::shared_ptr<PubSubAffiliation> > affiliations;
	};
}
