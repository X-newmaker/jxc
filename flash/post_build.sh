ProjDirPath=$1
ProjName=$2


${ProjDirPath}/tools/mk_private_resource.exe -l ${ProjDirPath}/Debug/private_partition.json,${ProjDirPath}/flash/private_bootpin_jtaglock.json -o ${ProjDirPath}/Debug/private_data.dat; 
${ProjDirPath}/tools/mk_prebootprog.exe -m "PDAT" -i ${ProjDirPath}/Debug/private_data.dat -o ${ProjDirPath}/Debug/private.bin; 
${ProjDirPath}/tools/mk_image.exe -v -c ${ProjDirPath}/flash/image_cfg.json -d ${ProjDirPath}/Debug/

echo ""
echo ""
echo "Auto-generated JTAG burn script start..."
${ProjDirPath}/tools/mk_burn_script.exe --config ${ProjDirPath}/flash/image_cfg.json --output ${ProjDirPath}/flash/jtag_burn.sh --firmware-dir ${ProjDirPath}/Debug --jtagburn ${ProjDirPath}/flash/JtagBurn.bin
echo "Auto-generated JTAG burn script done..."
