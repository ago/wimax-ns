#! /bin/sh
#############################################################################
#
# Copyright (c) 2007-2008, Intel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
# 
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  3. Neither the name of the Intel Corporation nor the names of its
#     contributors may be used to endorse or promote products derived from
#     this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################

# daemon install script 
# This file is used by Makefile to install the component

set -e

project_name=wimax_appsrv
daemon_name=wimax_appsrvd
bin_name=wimax_appsrvd
cubin_name=wimaxcu
updater_name=wimax_updater
daemon_script_name=wimax_appsrv
so_conf_file=wimax_appsrv.so.conf
target=

DESTDIR=${DESTDIR:-}
config_dir=$DESTDIR/etc/$project_name
ndns_config_dir=$DESTDIR/usr/share/$project_name
lib_dir=$DESTDIR/usr/lib/$project_name
bin_dir=$DESTDIR/usr/bin
updater_dir=$DESTDIR/usr/share/$project_name/$updater_name
log_dir=$DESTDIR/var/log/$project_name
pidfile_dir=$DESTDIR/var/run
lockfile_dir=$DESTDIR/var/lock/subsys
daemon_dir=$DESTDIR/etc/init.d
so_conf_dir=$DESTDIR/etc/ld.so.conf.d

create_dir()
{
    target_dir="$1"
    echo -n "   Creating $target_dir....."
    if [ ! -d $target_dir ]
    then 
        mkdir -p $target_dir && chmod 755 $1 $target_dir && echo "created [OK]"
    else
        echo "exist [OK]"
    fi
}

remove_dir()
{
    target_dir="$1"
    echo -n "   Removing $target_dir....."
    if [ -d $target_dir ]
    then 
        if [ -z "`ls $target_dir`" ]
	then
	    rm -rf $target_dir && echo "removed [OK]"	    
	else
	    echo "is not empty [OK]"
	fi
    else
        echo "does not exist [OK]"
    fi    
}

copy_file()
{
    source_dir="$1"
    source_file="$2"
    target_dir="$3"
    target_file=
    if [ ! "$4" ]
    then 
        target_file=$2
    else
        target_file=$4
    fi
        
    echo -n "   Copying $source_file to $target_dir....."
    if [ ! -f "$source_dir/$source_file" ]
    then
        echo "source $source_dir/$source_file NOT EXIST [FAIL]"
        return 1
    fi
    
    [ -f $target_dir/$target_file ] && rm -f $target_dir/$target_file
    
    cp $source_dir/$source_file $target_dir/$target_file
    echo "copied [OK]" 
}

delete_file()
{
    target_dir="$1"
    target_file="$2"
    
    echo -n "   Deleting $target_dir/$target_file....."
    if [ -f $target_dir/$target_file ]
    then
        rm -f $target_dir/$target_file && echo "deleted [OK]"
    else
        echo "does not exist [OK]"
    fi    
}

link_file()
{
    source_dir="$1"
    target_dir="$1"
    source_file="$2"
    target_file="$3"
        
    echo -n "   Linking $source_file to $target_file....."
    if [ ! -f "$source_dir/$source_file" ]
    then
        echo "source $source_dir/$source_file NOT EXIST [FAIL]"
        return 1
    fi
    
    [ -f $target_dir/$target_file ] && rm -f $target_dir/$target_file
    curr_dir=`pwd`
    cd $source_dir 
    ln -s $source_file $target_file
    cd $curr_dir
    echo "linked [OK]" 
}

delete_link()
{
    target_dir="$1"
    target_file="$2"
    
    echo -n "   Deleting $target_dir/$target_file....."
    if [ -s $target_dir/$target_file ]
    then
        rm -f $target_dir/$target_file && echo "deleted [OK]"
    else
        echo "does not exist [OK]"
    fi    
}

install_daemon()
{  
    # config dir
    echo "###  config.xml  ###"
    if [ -e $config_dir/config.xml ] ; then
	echo "    $config_dir/config.xml exists, not overwritten"
    else
    	create_dir $config_dir
    	copy_file $output_dir config.xml $config_dir
    fi
        
    echo "###  bootstrap.xml  ###"
    if [ -e $config_dir/bootstrap.xml ] ; then
	echo "    $config_dir/bootstrap.xml exists, not overwritten"
    else
    	create_dir $config_dir
    	copy_file $output_dir bootstrap.xml $config_dir
    fi


    # NDnS config dir
    echo ""
    echo "###  NDnSAgent config for driver  ###"
    create_dir $ndns_config_dir
    copy_file $output_dir NDnSAgentConfig_forDriver.xml $ndns_config_dir  
    copy_file $output_dir NDnSAgentDefaultConfig.xml $ndns_config_dir
    copy_file $output_dir DefaultTracesAndMonitors.xml $ndns_config_dir

    # so lib dir
    echo ""
    echo "###  so files  ###"
    create_dir $lib_dir
    copy_file $output_dir libL5Dispatcher.so $lib_dir
    copy_file $output_dir libPipeHandler.so $lib_dir
    copy_file $output_dir libiWmxSDK.so $lib_dir
    copy_file $output_dir libServices.so $lib_dir
    copy_file $output_dir libosal.so $lib_dir

    create_dir $so_conf_dir
    copy_file $PWD/scripts $so_conf_file $so_conf_dir

    if ! ldconfig
    then
        echo "WARNING: ldconfig failed (not enough permssions?)"
    fi

    echo ""
    echo "###  binaries  ###"
    create_dir $bin_dir
    copy_file $output_dir wimax_appsrvd $bin_dir
    copy_file $output_dir wimaxcu $bin_dir

    echo ""
    echo "###  log directory  ###"
    create_dir $log_dir

    # copy daemon script
    echo ""
    echo "###  daemon script  ###"
    create_dir $daemon_dir
    copy_file $PWD/scripts $daemon_script_name.$target $daemon_dir $daemon_script_name
    echo "   NOTE: daemon script is not registered.  It will not start during the boot time"

    # copy updater file 
    echo ""
    echo "###  updater script  ###"
    create_dir $updater_dir
    cp -f $PWD/wimax_updater/* $updater_dir
    chmod +x $updater_dir/$updater_name
    [ -f $bin_dir/$updater_name ] && rm -f $bin_dir/$updater_name
    ln -sf /usr/share/wimax_appsrv/$updater_name/$updater_name $bin_dir/$updater_name  
}           

remove_daemon()
{
    # config dir
    echo ""
    echo "###  config.xml  ###"
    delete_file $config_dir config.xml
    remove_dir $config_dir

    # NDnS config dir
    echo ""
    echo "###  NDnSAgent config for driver  ###"
    delete_file $ndns_config_dir NDnSAgentConfig_forDriver.* 
    delete_file $ndns_config_dir NDnSAgentDefaultConfig.*
    delete_file $ndns_config_dir DefaultTracesAndMonitors.*
    remove_dir $ndns_config_dir
          
    # so lib dir
    echo ""
    echo "###  so files  ###"
    delete_file $lib_dir libL5Dispatcher.so
    delete_file $lib_dir libPipeHandler.so 
    delete_file $lib_dir libiWmxSDK.so 
    delete_file $lib_dir libServices.so 
    delete_file $lib_dir libosal.so 
    delete_file $so_conf_dir wimax_appsrv.so.conf 
    remove_dir $lib_dir
    if ! ldconfig
    then
        echo " WARNING: ldconfig failed (not enough permissions?)"
    fi

    echo ""
    echo "###  binaries  ###"
    delete_file $bin_dir wimax_appsrvd
    delete_file $bin_dir wimaxcu

    echo ""
    echo "###  log directory  ###"
    remove_dir $log_dir
    
    echo ""
    echo "###  daemon script  ###"
    delete_file $daemon_dir $daemon_script_name
    echo "   NOTE: daemon script is not registered.  It will not start during the boot time"
    
    
}

get_output_dir()
{
    case "$1" in
        Debug)
            config=Debug
            ;;
        Release)
            config=Release
            ;;
        *)
            print_usage
            ;;
    esac
    currdir=`pwd`
    output_dir=`pwd`/tools_projects/Pipe/build_output/$config
    cd $currdir
}    


print_usage()
{
    echo "Usage: install [Debug|Release] [ume|midinux]"
    echo "Usage: remove"
    exit 1
}

# main flow of the script
if [ $USER != root ] ; then
    echo Must be root to run this script.
    exit 1
fi

if [ ! -d tools_projects ] ; then
    echo Must be run from top lever folder.
    exit 1
fi

case "$1" in
    install)
        get_output_dir "$2"
        case "$3" in
            ume)
                target=ume
                ;;
            midinux)
                target=midinux
                ;;
            *)
                print_usage
                ;;
        esac
        install_daemon
        ;;
    remove)
        remove_daemon
        ;;
    *)
        print_usage
        ;;
esac
