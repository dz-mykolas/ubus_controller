include $(TOPDIR)/rules.mk

PKG_NAME:=libserialport
PKG_RELEASE:=1
PKG_VERSION:=1.0.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/sigrokproject/libserialport.git
PKG_SOURCE_VERSION:=6f9b03e597ea7200eb616a4e410add3dd1690cb1

CMAKE_BINARY_SUBDIR:=build
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/libserialport
	CATEGORY:=Libraries
	TITLE:=libserialport
endef

define Package/libserialport/description
	libserialport library package
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/.libs/libserialport.so.0.1.0 $(1)/usr/lib
	$(LN) libserialport.so.0.1.0 $(1)/usr/lib/libserialport.so
	$(LN) libserialport.so.0.1.0 $(1)/usr/lib/libserialport.so.0
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libserialport.h $(1)/usr/include
endef

define Package/libserialport/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/.libs/libserialport.so.0.1.0 $(1)/usr/lib
	$(LN) libserialport.so.0.1.0 $(1)/usr/lib/libserialport.so
	$(LN) libserialport.so.0.1.0 $(1)/usr/lib/libserialport.so.0
endef

$(eval $(call BuildPackage,libserialport))