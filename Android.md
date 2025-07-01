# Android

## What is Android?
Android is a mobile operating system developed primarily by Google, and it is used on a wide range of devices such as smartphones, tablets, smartwatches, TVs, automotive displays, and even some home appliances. It is built on top of the Linux kernel, which provides the foundation for managing hardware like the CPU, memory, and device drivers.

## Key Characteristics of Android

* **Type**: Android is an Operating System (OS), which means it manages all the hardware and software components of a device. It acts as a bridge between the physical hardware and the applications that users interact with.
* **Based On**: Android is based on the Linux kernel, which is a well-known, robust, and open-source kernel used in many server and desktop systems. On top of that, Android includes many other open-source libraries, such as:
    * `libc`: A standard C library used for system-level programming
    * `WebKit`: A browser engine used to display web pages in apps
* **User Interface (UI)**: Android’s user interface is designed primarily for touch-based interaction. Users interact with apps using gestures like tapping, swiping, pinching, and scrolling. In addition to touch, Android also supports:
    * Voice input (via Google Assistant or other tools)
    * Gesture-based navigation
    * Accessibility support like TalkBack, screen readers, and magnification

## Programming Languages Used in Android
Developers can build Android apps and system components using multiple programming languages, each with a specific role:

* **Java**:
    * Initially the main programming language for Android application development.
    * Apps run on the Android Runtime (ART) or previously the Dalvik Virtual Machine.
    * Many core Android APIs are written in Java.
* **Kotlin**:
    * In 2017, Google announced Kotlin as the officially recommended language for Android development.
    * Kotlin is more concise, safe, and modern compared to Java.
    * Fully interoperable with Java (you can mix both in the same project).
* **C/C++**:
    * Used mainly for low-level system components and performance-critical native applications.
    * Developers use the Android NDK (Native Development Kit) to write parts of an app in C/C++ (e.g., for games or audio processing).

## Device Categories that Use Android
Android is not limited to smartphones. It powers a wide range of smart and embedded devices, including:

* Smartphones (e.g., Samsung, OnePlus, Pixel, Vivo, Realme)
* Tablets (e.g., Samsung Galaxy Tab, Lenovo Tab)
* Smart TVs (Android TV and Google TV platforms)
* Wearables (Watches running Wear OS)
* Automotive Displays (Android Auto and Android Automotive OS)
* Smart Devices (fridges, speakers, projectors, etc., via Android Things or custom Android)

Android is a powerful, flexible, and open-source mobile operating system. Its Linux-based architecture, support for multiple programming languages, and adaptability across device types have made it the most widely used OS in the world for mobile and smart devices.

## History and Origin of Android (Detailed Explanation)
The story of Android is one of innovation, open-source philosophy, and global adoption. Here's a breakdown of how Android started and became the most widely used mobile OS in the world.

### 2003 – The Birth of Android Inc.
Android Inc. was founded in October 2003 in Palo Alto, California.

* **Founders**: Andy Rubin, Rich Miner, Nick Sears, and Chris White.
* **Initial Goal**: Develop software for digital cameras to allow users to upload photos to cloud storage. However, they soon realized the mobile phone market was more promising.
* Pivoted to building a flexible and open-source mobile OS to compete with existing systems like Symbian and Windows Mobile.

### 2005 – Google Acquires Android
In August 2005, Google acquired Android Inc. for approximately $50 million.

* All four founders joined Google.
* Android was kept secret at first; Google quietly worked on building an open mobile platform.

### 2007 – Open Handset Alliance (OHA) is Formed
In November 2007, Google publicly unveiled Android as part of the Open Handset Alliance, a consortium of hardware manufacturers, software developers, and mobile carriers.

* **Founding members included**:
    * HTC, Samsung, Sony, LG
    * Motorola
    * Qualcomm, Texas Instruments
    * Sprint, T-Mobile, Vodafone
* **Goal**: Create a free, open-source platform for mobile devices that would encourage innovation and reduce fragmentation in the mobile world.

### 2008 – First Android Phone Launched
The first Android smartphone was the HTC Dream, also known as the T-Mobile G1, released in September 2008.

* It included:
    * Touchscreen + physical QWERTY keyboard
    * Access to the Android Market (now Google Play)
    * Built-in Google apps like Gmail, Maps, YouTube
* It showed the potential of Android, despite being basic by today’s standards.

### Core Technologies Introduced:
* **Linux Kernel**: Android is built on top of the Linux kernel (just like Ubuntu or Red Hat), giving it stability, hardware control, and process management.
* **Dalvik Virtual Machine (DVM)**: Android apps were initially run in the Dalvik VM, which allowed multiple apps to run efficiently on low-memory devices. Later, Dalvik was replaced by ART (Android Runtime) for better performance.

## What Was Used Before Android?
Before Android’s rise, the mobile world had several competing operating systems, most of which were proprietary, closed-source, and not designed for modern touch interaction.

The major ones:

### 1. Symbian OS
* **Used By**: Mainly Nokia, also by Sony Ericsson and others.
* **Features**:
    * Multitasking
    * Customizable UI
    * Good for non-touch phones
* **Limitations**:
    * Poor touchscreen support
    * Difficult to develop for (complex SDK)
    * Closed development process
* Symbian began to lose ground around 2010 when Nokia failed to transition fast to touchscreen phones.

### 2. Java ME (J2ME)
* **Used In**: Low-end feature phones (basic phones, not smartphones).
* **Features**:
    * Lightweight apps (games, SMS tools)
    * Runs on very limited hardware
* **Limitations**:
    * Not a full operating system
    * No multitasking or deep hardware access
    * No app store; users installed .jar files manually
* Java ME apps were common in the 2000s, but the platform wasn’t designed for rich apps or internet connectivity.

### 3. Windows Mobile
* **Developed By**: Microsoft.
* **Used In**: HTC, Motorola, Dell Axim, and other PDAs.
* **Features**:
    * Strong integration with Microsoft Office
    * Stylus-based interface
* **Limitations**:
    * Poor touch experience
    * Outdated UI
    * Not consumer-friendly
* Microsoft later replaced it with Windows Phone, but it failed due to poor app support.

### 4. BlackBerry OS
* **Used By**: BlackBerry (formerly RIM).
* **Features**:
    * Full QWERTY keyboards
    * Excellent security
    * Email and BBM (BlackBerry Messenger)
* **Limitations**:
    * No touchscreen UI in early versions
    * Weak multimedia and app ecosystem
    * Not attractive to general consumers
* BlackBerry was dominant in business, but couldn’t adapt to the app-centric smartphone revolution.

### 5. Palm OS
* **Used By**: Palm devices like Palm Treo.
* **Features**:
    * Early stylus UI
    * Personal organizer tools
* **Limitations**:
    * No hardware acceleration
    * No modern UI
    * Poor app and web support
* Palm eventually developed WebOS, but it couldn’t compete and was sold to HP.

## Common Problems with Pre-Android Systems:

| Issue | Explanation |
| :---------- | :---------- |
| Closed-source | No flexibility for OEMs or developers |
| Weak App Ecosystem | No large-scale app stores or SDKs |
| Limited UI Design | Most were not built for touchscreens |
| Fragmentation | Each vendor had their own way of doing things |
| Hard to Update | No easy OTA (over-the-air) updates |

## Why Android Was a Game Changer:

| Strength | How It Helped Android |
| :---------- | :---------- |
| Open-source | Anyone could build on it or modify it |
| Touch-first Design | Designed from scratch for modern smartphones |
| Free to Use | Manufacturers loved the cost savings |
| Strong Google Services | Built-in Gmail, YouTube, Maps, etc. |
| Easy App Development | Free tools like Android Studio, large dev community |
| App Store | Google Play allowed direct publishing, monetization, updates |
