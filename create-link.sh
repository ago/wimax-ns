
cd tools_projects/Pipe/Wrappers/CommonAPI

if [ -f wimax_osal_types.h ]; 
then 
	echo 'Skipping creating sym link'; 
else 
	ln -s ../../Services/osal/wimax_osal_types.h wimax_osal_types.h; 
fi
