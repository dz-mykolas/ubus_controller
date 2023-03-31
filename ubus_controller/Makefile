include $(TOPDIR)/rules.mk

PKG_NAME:=ubus_controller
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/ubus_controller
	CATEGORY:=Base system
	TITLE:=ubus_controller
	DEPENDS:=+libserialport +libubus +libubox +libblobmsg-json
endef

define Package/ubus_controller/description
	Controller through ubus
endef

define Package/ubus_controller/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ubus_controller $(1)/usr/bin
	$(INSTALL_BIN) ./files/ubus_controller.init $(1)/etc/init.d/ubus_controller
endef

$(eval $(call BuildPackage,ubus_controller))