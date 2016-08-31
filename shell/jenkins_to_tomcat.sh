#! /bin/bash
########################################
#create by john
#date 2016.8.31 14:57
#version: 1.0.1
########################################
source /etc/profile
source ~/.bash_profile
PS="/usr/bin/ps -ef"
GREP="/usr/bin/grep -E"
AWK="/usr/bin/awk"
KILL="/usr/bin/kill -9"
FIND="/usr/bin/find"
TAR="/usr/bin/tar -czf"
DATE="/usr/bin/date +%Y-%m-%d_%H%M%S"
lDATE="/usr/bin/date '+[%Y-%m-%d %H:%M:%S]'"
SH="/usr/bin/sh"
PRT="/usr/bin/printf"
##################write and print log##########################
log() {
	$PRT "$(/usr/bin/date '+[%Y-%m-%d %H:%M:%S]') $1\n"
}
########################kill The process(tomcat)########################
killpro() {
	PID=`$PS|$GREP "java(.*)$1"|$GREP -v "grep"|$AWK '{print $2}'`
	if [ ! -f ${TOMCAT_BIN}/startup.sh ]
	then
		log "Tomcat Is Not In ${TOMCAT_BIN}. Please Check Tomcat Path."
		exit
	fi
	if [[ "$PID" == "" ]]
	then
		log "Tomcat Is Not Running"
		log "We Will Be Ignore STOP, Going To Update And Start."
		return 1
	else
		log "Tomcat $1 PID == $PID"
		stdou=$($KILL $PID 2>&1) ; stat=$?
		if [[ $stat == 0 ]]
		then
			log "Kill PID=$PID Process Ok."
			return 0
		else
			log "Kill PID=$PID Process ERROR: $stdou"
			return 1
		fi
	fi
}
#################################check src path and file#########################
findsrcpath() {
	if [ ! -f $1/$2 ]
	then
		log "The Src Path $1/$2 Fault. Please Check This Files Path."
		return 1
	fi
	log "check new package $1/$2 Ok."
	return 0
}
####################################back old war###################################
BackupDesc() {
	cudir=$(pwd)
	if [ ! -d $1 ]
	then
		log "The Desc Path $1 Fault. Please Check This Path Files."
		return 1
	fi
	if [ ! -d $2 ]
	then
		log "backup directory not exist, we will be create dir $2"
		/usr/bin/mkdir -p $2
	fi
	obj=$(echo $3|$AWK -F'.' '{print $1}')
	backup_name=$2/${obj}_$($DATE).tar.gz
	cd $1
	log "backup old object to ${backup_name}......"
	jeguo=$($TAR ${backup_name} ./*); stat=$?
	cd $cudir
	if [[ $stat != 0 ]]
	then
		log "Backup Dest $1 Error."
		log "$jeguo"
		return 1
	fi
	log "backup old object to ${backup_name}...... done"
	return 0
}
###########################update war package########################
moveto() {
	if [[ $1 == "" ]] || [[ $2 == "" ]]
	then
		log "Moveto Fun Error, args[1] or args[2] is NULL."
		exit 3
	fi
	mv $2/${OBJPKG_NAME} $2/${OBJPKG_NAME}.$($DATE)
	objname=$2/$(echo ${OBJPKG_NAME}|$AWK -F'.' '{print $1}')
	if [ -d ${objname} ] && [[ ${objname} =~ ${TOMCAT_PATH} ]]
	then
		log "delete old object directory ${objname}"
		rm -rf ${objname}
	fi
	mv $1/${OBJPKG_NAME} $2/${OBJPKG_NAME}
	log "update new war package to $2/${OBJPKG_NAME}"
	return 0
}
#################################startup############################
startpro() {
	jeguo=$($SH $1/startup.sh 2>&1); stat=$?
	if [[ $stat != 0 ]]
	then
		log "Start $1 Process Error"
		return 1
	fi
	log "startup tomcat ${1}.....done"
	return 0
}
#############################check exec status###################
ErrExit() {
	if [[ $1 != 0 ]]
	then
		log "Error Exit."
		exit 2
	fi
}
############################help info#############################
helpinfo() {
	$PRT "\n"
	$PRT "Eg: $1 BACKUP_PATH=/path/to/backup \\"
	$PRT "\n"
	$PRT "\tUPDATE_PATH=/path/to/jenkins/uploaddir \\"
	$PRT "\n"
	$PRT "\tTOMCAT_PATH=/path/to/jenkins/uploaddir \\"
	$PRT "\n"
	$PRT "\tOBJPKG_NAME=war_package_name.war"
	$PRT "\n"
	$PRT "\n"
	$PRT "DESCRIPTION\n"
	$PRT "\tBACKUP_PATH: backup directory\n"
	$PRT "\tUPDATE_PATH: jenkins upload to romote directory\n"
	$PRT "\tOBJPKG_NAME: object package name\n"
	$PRT "\tTOMCAT_PATH: tomcat home path\n"
	$PRT "Warning: Please use the absolute path\n\n"
}
#############################parameter init#####################
paminit() {
	if [[ $# != 4 ]]
	then
		log ""
		log "$0 need 4 args, args number error."
		helpinfo $0
		return 1
	fi
	BACKUP_PATH=""
	UPDATE_PATH=""
	OBJPKG_NAME=""
	TOMCAT_PATH=""
	for i in $*
	do
		key=$(echo $i|awk -F'=' '{print $1}')
		val=$(echo $i|awk -F'=' '{print $2}')
		if [[ $key == "" ]] || [[ $val == "" ]]
		then
			log "args[$i] key or value is null."
			helpinfo $0
			return 1
		fi
		if [[ $key == "BACKUP_PATH" ]]
		then
			BACKUP_PATH=$val
		elif [[ $key == "UPDATE_PATH" ]]
		then
			UPDATE_PATH=$val
		elif [[ $key == "OBJPKG_NAME" ]] 
                then
			OBJPKG_NAME=$val
		elif [[ $key == "TOMCAT_PATH" ]]
                then
                        TOMCAT_PATH=$val
		else
			log "args[$i] key Error."
			helpinfo $0
			return 1
		fi
	done
	TOMCAT_WEBP="${TOMCAT_PATH}/webapps"
	TOMCAT_BIN="${TOMCAT_PATH}/bin"
	return 0
}
#####################MAIN#######################################
paminit $*;stat=$?
ErrExit $stat
findsrcpath ${UPDATE_PATH} ${OBJPKG_NAME}; stat=$?
ErrExit $stat
BackupDesc "${TOMCAT_WEBP}" "${BACKUP_PATH}" "${OBJPKG_NAME}"; stat=$?
ErrExit $stat
killpro "$TOMCAT_BIN"
moveto "${UPDATE_PATH}" "${TOMCAT_WEBP}"; stat=$?
ErrExit $stat
startpro "${TOMCAT_BIN}"; stat=$?
ErrExit $stat
