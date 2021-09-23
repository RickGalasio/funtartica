#!/bin/bash

if [ ! -f android-sdk_r24.4.1-linux.tgz ] ; then
   curl -O https://dl.google.com/android/android-sdk_r24.4.1-linux.tgz
fi
tar zxf android-sdk_r24.4.1-linux.tgz
mkdir android-sdk-linux/build-tools

if [ ! -f build-tools_r25-linux.zip ] ; then
   curl -O https://dl.google.com/android/repository/build-tools_r25-linux.zip
fi
unzip build-tools_r25-linux.zip
mv android-7.1.1 android-sdk-linux/build-tools/25.0.0

if [ ! -f android-16_r05.zip ] ; then
   curl -O https://dl.google.com/android/repository/android-16_r05.zip
fi
unzip android-16_r05.zip
mv android-4.1.2 android-sdk-linux/platforms/android-16

 
if [ ! -f platform-tools_r25-linux.zip ] ; then
   curl -O https://dl.google.com/android/repository/platform-tools_r25-linux.zip
fi
unzip platform-tools_r25-linux.zip -d android-sdk-linux/

export SDK="$(pwd)/android-sdk-linux"
export BUILD_TOOLS="${SDK}/build-tools/25.0.0"
export PLATFORM="${SDK}/platforms/android-16"
 
#mkdir -p build/gen build/obj build/apk

cd command_line_android
mkdir -p build/gen build/obj build/apk
"${BUILD_TOOLS}/aapt" package -f -m -J build/gen/ -S res -M AndroidManifest.xml -I "${PLATFORM}/android.jar"
cd ../ 

tar xvf jdk-8u202-linux-x64.tar.gz 
export JAVA_HOME=$(pwd)/jdk1.8.0_202
export PATH=${JAVA_HOME}/bin:$PATH
cd command_line_android/
javac -source 1.7 -target 1.7 -bootclasspath "${JAVA_HOME}/jre/lib/rt.jar" -classpath "${PLATFORM}/android.jar" -d build/obj build/gen/net/hanshq/hello/R.java java/net/hanshq/hello/MainActivity.java
"${BUILD_TOOLS}/dx" --dex --output=build/apk/classes.dex build/obj/
"${BUILD_TOOLS}/aapt" package -f -M AndroidManifest.xml -S res/ -I "${PLATFORM}/android.jar" -F build/Hello.unsigned.apk build/apk/
"${BUILD_TOOLS}/zipalign" -f -p 4 build/Hello.unsigned.apk build/Hello.aligned.apk
keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -keysize 2048 -storepass android -keypass android
"${BUILD_TOOLS}/apksigner" sign --ks keystore.jks --ks-key-alias androidkey --ks-pass pass:android --key-pass pass:android --out build/Hello.apk build/Hello.aligned.apk

 find ./ -iname "*.apk"

