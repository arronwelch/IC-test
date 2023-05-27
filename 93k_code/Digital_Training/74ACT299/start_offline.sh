# shell for start multi-SMT7 in offline
# /opt/hp93000/soc_common/bin/switch_version soc64_7.5.4.2
# /opt/hp93000/soc_common/bin/switch_version soc64_7.5.1.0
export V93000_MODEL=./offline.model
DISPLAY_HP83000="SMT7_Training"
/opt/hp93000/soc/prod_env/bin/HPSmarTest -o&

# show mac address:
# $ /sbin/ifconfig
# $ cat /sys/class/net/*/address

# model file path:
# $ /etc/opt/hp93000/soc/model

# license file path:
# $ /opt/flexlm/license

