/*
 * Copyright (c) 2011-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/SafeByteArray.h>
#include <Swiften/Base/SafeString.h>
#include <Swiften/Elements/StreamType.h>
#include <Swiften/EventLoop/EventOwner.h>
#include <Swiften/Network/BOSHConnectionPool.h>
#include <Swiften/Session/SessionStream.h>
#include <Swiften/TLS/TLSOptions.h>


namespace Swift {
	class TimerFactory;
	class PayloadParserFactoryCollection;
	class PayloadSerializerCollection;
	class StreamStack;
	class XMPPLayer;
	class ConnectionLayer;
	class CompressionLayer;
	class XMLParserFactory;
	class TLSContextFactory;
	class EventLoop;

	class SWIFTEN_API BOSHSessionStream : public SessionStream, public EventOwner, public boost::enable_shared_from_this<BOSHSessionStream> {
		public:
			BOSHSessionStream(
					const URL& boshURL,
					PayloadParserFactoryCollection* payloadParserFactories,
					PayloadSerializerCollection* payloadSerializers,
					ConnectionFactory* connectionFactory,
					TLSContextFactory* tlsContextFactory,
					TimerFactory* whitespacePingLayerFactory,
					XMLParserFactory* xmlParserFactory,
					EventLoop* eventLoop,
					DomainNameResolver* resolver,
					const std::string& to,
					const URL& boshHTTPConnectProxyURL,
					const SafeString& boshHTTPConnectProxyAuthID,
					const SafeString& boshHTTPConnectProxyAuthPassword,
					const TLSOptions& tlsOptions
			);
			~BOSHSessionStream();

			virtual void close();
			virtual bool isOpen();

			virtual void writeHeader(const ProtocolHeader& header);
			virtual void writeElement(boost::shared_ptr<ToplevelElement>);
			virtual void writeFooter();
			virtual void writeData(const std::string& data);

			virtual bool supportsZLibCompression();
			virtual void addZLibCompression();

			virtual bool supportsTLSEncryption();
			virtual void addTLSEncryption();
			virtual bool isTLSEncrypted();
			virtual Certificate::ref getPeerCertificate() const;
			virtual std::vector<Certificate::ref> getPeerCertificateChain() const;
			virtual boost::shared_ptr<CertificateVerificationError> getPeerCertificateVerificationError() const;
			virtual ByteArray getTLSFinishMessage() const;

			virtual void setWhitespacePingEnabled(bool);

			virtual void resetXMPPParser();

		private:
			void handleXMPPError();
			void handleStreamStartReceived(const ProtocolHeader&);
			void handleElementReceived(boost::shared_ptr<ToplevelElement>);
			void handlePoolXMPPDataRead(const SafeByteArray& data);
			void handleXMPPLayerDataWritten(const SafeByteArray& data);
			void handlePoolSessionStarted();
			void handlePoolBOSHDataRead(const SafeByteArray& data);
			void handlePoolBOSHDataWritten(const SafeByteArray& data);
			void handlePoolSessionTerminated(BOSHError::ref condition);

		private:
			void fakeStreamHeaderReceipt();
			void fakeStreamFooterReceipt(BOSHError::ref error);

		private:
			BOSHConnectionPool* connectionPool;
			bool available;
			XMPPLayer* xmppLayer;
			ProtocolHeader streamHeader;
			EventLoop* eventLoop;
			bool firstHeader;
	};

}
