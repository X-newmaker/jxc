# set *0x18020800 = 0x100000	: enable syscfg cmu
# set *0x18000160 = 0xA1C00000	： disable tcm
# set $mitcmcr=0				: disable tcm
# set $mdtcmcr=0				: disable tcm

# reset chip
reset

# disable tcm.
set *0x18020800 = 0x100000
set *0x18000160 = 0xA1C00070
set $mitcmcr=0x30040001
set $mdtcmcr=0x30080001
