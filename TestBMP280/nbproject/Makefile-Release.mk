#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-linux-gnueabihf-gcc
CCC=arm-linux-gnueabihf-c++
CXX=arm-linux-gnueabihf-c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=ARM-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/MyLib/GeFunctions/geTime.o \
	${OBJECTDIR}/MyLib/I2C/I2CLib.o \
	${OBJECTDIR}/Sensors/BME280/bme280.o \
	${OBJECTDIR}/Sensors/BME280/bme290_impl.o \
	${OBJECTDIR}/Server/json.o \
	${OBJECTDIR}/TestBench.o \
	${OBJECTDIR}/Web_Server/mongoose.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sqlite/sqldriver.o \
	${OBJECTDIR}/sqlite/sqlite3.o


# C Compiler Flags
CFLAGS=-lm -pthread

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbmp280

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbmp280: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testbmp280 ${OBJECTFILES} ${LDLIBSOPTIONS} -ldl

${OBJECTDIR}/MyLib/GeFunctions/geTime.o: MyLib/GeFunctions/geTime.c
	${MKDIR} -p ${OBJECTDIR}/MyLib/GeFunctions
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLib/GeFunctions/geTime.o MyLib/GeFunctions/geTime.c

${OBJECTDIR}/MyLib/I2C/I2CLib.o: MyLib/I2C/I2CLib.c
	${MKDIR} -p ${OBJECTDIR}/MyLib/I2C
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLib/I2C/I2CLib.o MyLib/I2C/I2CLib.c

${OBJECTDIR}/Sensors/BME280/bme280.o: Sensors/BME280/bme280.c
	${MKDIR} -p ${OBJECTDIR}/Sensors/BME280
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sensors/BME280/bme280.o Sensors/BME280/bme280.c

${OBJECTDIR}/Sensors/BME280/bme290_impl.o: Sensors/BME280/bme290_impl.c
	${MKDIR} -p ${OBJECTDIR}/Sensors/BME280
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sensors/BME280/bme290_impl.o Sensors/BME280/bme290_impl.c

${OBJECTDIR}/Server/json.o: Server/json.c
	${MKDIR} -p ${OBJECTDIR}/Server
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/json.o Server/json.c

${OBJECTDIR}/TestBench.o: TestBench.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestBench.o TestBench.c

${OBJECTDIR}/Web_Server/mongoose.o: Web_Server/mongoose.c
	${MKDIR} -p ${OBJECTDIR}/Web_Server
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Web_Server/mongoose.o Web_Server/mongoose.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/sqlite/sqldriver.o: sqlite/sqldriver.c
	${MKDIR} -p ${OBJECTDIR}/sqlite
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sqlite/sqldriver.o sqlite/sqldriver.c

${OBJECTDIR}/sqlite/sqlite3.o: sqlite/sqlite3.c
	${MKDIR} -p ${OBJECTDIR}/sqlite
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sqlite/sqlite3.o sqlite/sqlite3.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
