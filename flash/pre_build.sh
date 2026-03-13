ProjDirPath=$1

${ProjDirPath}/tools/cp.exe ${ProjDirPath}/flash/uploader*  ${ProjDirPath}/Debug/
${ProjDirPath}/tools/cp.exe ${ProjDirPath}/flash/bootloader*  ${ProjDirPath}/Debug/
${ProjDirPath}/tools/cp.exe ${ProjDirPath}/flash/aes_iv.bin ${ProjDirPath}/flash/aes_ssk.bin ${ProjDirPath}/Debug/
${ProjDirPath}/tools/gen_partition_table.exe -c ${ProjDirPath}/flash/image_cfg.json -o ${ProjDirPath}/partition_table.h -j ${ProjDirPath}/Debug/private_partition.json;
