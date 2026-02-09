# 🟢 Circular QR / Circular Code Recognition Engine

<img width="375" height="643" alt="1" src="https://github.com/user-attachments/assets/56f1bd01-f85b-4cec-90a9-ca591865bf3c" />


A mobile sample project (Xamarin C# + native engine) that demonstrates a circular QR / circular code recognition engine.  
The core recognition engine is native C++/Objective‑C (FindRecogDigit + RnOCR) with Xamarin bindings so the app can call the engine from C#.

---

## 🧭 About

RnOCRReader is a small demo application and library that:
- Captures camera frames (iOS example: AVFoundation).
- Crops the capture area and passes an image to a native circular QR/circular-code recognition engine.
- Returns a short string result (UUID-like value) if recognition succeeds, or numeric error/status codes otherwise.
- Provides a Xamarin binding to call the native engine from C# (iOS binding included).

The name RnOCR highlights its purpose: Recognition (Rn) — OCR-like pipeline for circular QR / circular-code style patterns.

---

## 📷 Screenshot

<img width="1629" height="640" alt="qr code image samples" src="https://github.com/user-attachments/assets/8a734605-3258-46af-8ff1-c39617e09c4b" />
<img width="500" height="500" alt="qr_code_arc_numbers" src="https://github.com/user-attachments/assets/bb0e4c3a-7b66-447c-86d3-3e7001840e6c" />
<img width="500" height="500" alt="qr_code_example" src="https://github.com/user-attachments/assets/6332b31d-30b6-4e14-9d1f-24f4e389bc0c" />
<img width="500" height="500" alt="qr_code_pattern" src="https://github.com/user-attachments/assets/178858d6-597d-4f3f-89a9-1c8cd9edad5e" />

---

## ✨ Key Features

- ✅ Native circular QR / circular-code recognition engine (C++/Objective‑C)
- ✅ Prebuilt iOS static library included (libRnOCR.a)
- ✅ Xamarin iOS binding (RnOCRBinding) — call engine from C#
- ✅ Live camera capture + crop + recognition demo (CaptureViewController)
- ✅ Cross-project layout: iOS app, Android shell, native engine source and build scripts

---

## 🚀 Quickstart

Prerequisites:
- macOS with Xcode (for building native engine and iOS app)
- Visual Studio for Mac or Visual Studio (Windows) with Xamarin for C# projects
- .NET / Xamarin toolchain installed
- Optional: Android SDK & emulator for Android project

### iOS — Build & Run (Xamarin.iOS)

1. Open the solution:
   - Open `ios/RnOCRReader.sln` in Visual Studio for Mac (or Visual Studio with Xamarin on macOS).
2. Ensure the native static library is present:
   - `ios/RnOCRBinding/libRnOCR.a` is already included (prebuilt). If you want to rebuild the native library from source, see the Native Engine section below.
3. Add camera usage description:
   - Before distributing on the App Store, add `NSCameraUsageDescription` to `ios/iOS/Info.plist` with a user-visible string. Example:
     ```
     <key>NSCameraUsageDescription</key>
     <string>This app requires the camera to capture codes for recognition.</string>
     ```
4. Build & run on device (recommended) or simulator (simulator support requires the iOS simulator slice in lib):
   - Select `RnOCRReader.iOS` project and run.

Notes:
- The sample's recognition is invoked in `ios/iOS/CaptureViewController.cs` via the binding:
  ```csharp
  string uuid = RnOCR.Recog(cropImage, rst: state);
  ```
  The method returns a short string (recognized ID) or numeric status codes.

### Android — Build & Run (Xamarin.Android)

1. Open the solution in Visual Studio.
2. Android project is in `ios/Droid/`.
3. Add camera permission to `ios/Droid/Properties/AndroidManifest.xml` (it currently lacks CAMERA):
   ```xml
   <uses-permission android:name="android.permission.CAMERA" />
   <uses-feature android:name="android.hardware.camera" android:required="false" />
   ```
4. Implement native integration for the OCR engine on Android:
   - The repository includes Android project scaffolding, but the native engine packaging for Android (.so or .aar) is not included. You will need to port or compile the engine into Android native libraries and call them through JNI or Xamarin bindings.

---

## 🛠 Native Engine — Build from source (iOS)

The engine build script is here:
- engine/library/Makefile

It expects an Xcode project inside `engine/library/RnOCR` and will produce architecture-specific `.a` files and a fat library via `lipo`.

Common commands (macOS + Xcode):
```bash
cd engine/library
# Build per-arch and create a fat lib
make libRnOCR.a

# If you prefer manual steps, the Makefile uses xcodebuild and lipo:
# xcodebuild -project ./RnOCR/RnOCR.xcodeproj -target RnOCR -sdk iphonesimulator -configuration Release clean build
# xcodebuild -project ./RnOCR/RnOCR.xcodeproj -target RnOCR -sdk iphoneos -arch armv7 -configuration Release clean build
# xcrun lipo -create -output libRnOCR.a [list of .a slices...]
```

Important notes:
- The Makefile targets show a 3-slice build: i386 (simulator), armv7, arm64.
- After building, copy the resulting fat `libRnOCR.a` into `ios/RnOCRBinding/` (or update your binding settings).

---

## 🔍 How Recognition Works (developer notes)

- The Objective‑C wrapper `RnOCR` exposes:
  ```objc
  + (NSString *)recog:(UIImage *)img rstName:(NSString *)rst;
  ```
  (See: engine/library/RnOCR/RnOCR.h and .m)

- The implementation converts a UIImage -> DIB -> gray image and calls the native recognizer:
  - The recognizer entry point is `CFindRecogDigit::Find_RecogGrayImg(grayImg, w, h, uuid)`
  - Present in `engine/library/RnOCR/FindRecogDigit.*`

- Return values (observed behavior):
  - returns `"2"`: special status (engine-specific)
  - returns a string like `"..."` (UUID) on successful recognition (nret == 1)
  - returns numeric string like `"-1"` or `"-2"` on errors (e.g., failure to convert image)

- C# binding to call this from Xamarin:
  ```csharp
  // RnOCRBinding/ApiDefinition.cs exposes:
  // [Export("recog:rstName:")] string Recog(UIImage img, string rst);
  string result = RnOCR.Recog(croppedUIImage, rst: "");
  ```

---

## 🧩 Project Structure (deep level)

Root (top-level)
- ios/
  - RnOCRReader.sln — Visual Studio solution (iOS + Android + binding)
  - RnOCRReader/ — shared portable class library
  - RnOCRReader.iOS/ — iOS app project
    - AppDelegate.cs — app lifecycle
    - Main.cs — app entry
    - CaptureViewController.cs — camera capture and recognition logic (core demo)
    - Info.plist — App configuration (add NSCameraUsageDescription here)
    - LaunchScreen.storyboard / Main.storyboard — UI
    - Assets.xcassets — app icons (replace screenshot here)
  - RnOCRBinding/ — Xamarin.iOS binding project
    - ApiDefinition.cs — binding interface for RnOCR
    - Structs.cs — any required native struct mappings
    - libRnOCR.a — prebuilt native library (static)
    - libRnOCR.linkwith.cs — binding characteristics for the native lib
- engine/
  - library/
    - Makefile — build script for native iOS static libs (xcodebuild + lipo)
    - RnOCR/ — Xcode project implementing the native engine
      - RnOCR.h / RnOCR.m — Objective-C wrapper
      - FindRecogDigit.cpp / .h — core recognition logic (C++ code)
      - ImageBase.*, uiimage2DIB.* — helpers for image conversion and processing
    - ApiDefinitions.cs — (duplicate binding template, used in some workflows)
  - result/
    - libRnOCR-*.a — example or older build outputs
- windows/
  - demo/ — Windows demo code with a lot of third party imaging libs (CxImage, libjpeg, png, zlib, etc.)
  - dll/TestDll/ — example DLL wrapper for windows platform
- ios/Droid/
  - MainActivity.cs — Android sample launcher/activity
  - Properties/AndroidManifest.xml — android manifest (add CAMERA permission)
- Misc vendor folders: `windows/demo/CxImage/`, contains imaging codecs used by engine or demo.

Important engine files to review:
- engine/library/RnOCR/RnOCR.m — bridge from UIImage -> DIB -> C++ recognizer
- engine/library/RnOCR/FindRecogDigit.* — recognition algorithm
- engine/library/Include/myType.h — shared type definitions used by the engine

---

## 🧰 Tech Stack & Libraries

- Languages:
  - Objective‑C (iOS glue)
  - C / C++ (recognition engine)
  - C# (Xamarin / UI)
- Mobile frameworks:
  - iOS: AVFoundation, UIKit
  - Xamarin.iOS, Xamarin.Android (C#)
- Build tools:
  - Xcode / xcodebuild, lipo (native)
  - Visual Studio / MSBuild (Xamarin)
- Libraries & third-party code (included under windows/demo/CxImage and engine):
  - CxImage, libjpeg, libpng, libtiff, zlib, Jasper (some older image codec code appears in repo)
- Binding:
  - Xamarin Objective-C binding (ApiDefinition.cs / RnOCRBinding)

---

## ✅ Usage Examples

C# (Xamarin.iOS)
```csharp
// CaptureViewController.cs excerpt:
// After cropping to a UIImage `cropImage`:
string result = RnOCR.Recog(cropImage, rst: "");
if (result.Length > 2) {
    // success — result is the recognized ID string
    lblResult.Text = result;
} else {
    // failure or special status; engine returns strings like "2" or "-1"
    lblResult.Text = "";
}
```

Objective‑C (native call, if consuming RnOCR directly)
```objc
#import "RnOCR.h"
UIImage *image = ...; // your UIImage
NSString *result = [RnOCR recog:image rstName:@""];
if (result.length > 2) {
    NSLog(@"Recognized: %@", result);
} else {
    NSLog(@"Status/Error: %@", result);
}
```

---

## ⚠️ Platform Notes & Known Issues

- iOS privacy: Info.plist must include NSCameraUsageDescription (and NSPhotoLibraryAddUsageDescription if saving).
- Android: `ios/Droid/Properties/AndroidManifest.xml` currently does not include CAMERA permission. Add:
  ```xml
  <uses-permission android:name="android.permission.CAMERA" />
  ```
- Prebuilt library: `ios/RnOCRBinding/libRnOCR.a` is included, but if you have a mismatched architecture you must rebuild using the Makefile and ensure the fat library contains simulator and device slices.
- Android engine: Native Android library (.so) is not included. Port/compile the engine for Android separately if you need Android native recognition.

---

## 🔭 Future Roadmap (Table)

| Feature / Improvement | Status | Priority | Notes |
|---|---:|---:|---|
| Add NSCameraUsageDescription to Info.plist | Needed | High | Required for App Store and runtime camera access |
| Add Android native library (.so) + JNI binding | Planned | High | Enables recognition on Android devices |
| Improve recognition accuracy & testing dataset | Planned | Medium | Add more test images & unit tests for recognition |
| Add CI builds (macOS) for native engine | Planned | Medium | Automate building lib for supported archs |
| Add sample images & screenshots to docs | Planned | Low | Makes README screenshot section richer |
| Convert native engine to a packaged cross-platform lib | Idea | Low | e.g., CMake build, produce .a/.so for multiple platforms |

---

## 🤝 Contributing

- Fork the repo and open a pull request with a clear description.
- If you change the native engine, please document how to rebuild and include the new slices in `libRnOCR.a`.
- For Android support: propose a strategy (JNI wrapper, or port engine to CMake) and include build instructions.

---

## 📜 License

This project is licensed under the MIT License — see [LICENSE](LICENSE).

---

## 📬 Contact / Help

If you need help:
- Open an issue in this repository with detailed logs and platform info.
- Include sample images that cause recognition problems (if accuracy work is required).

---

Thank you for sharing your project — the circular QR / circular-code recognition engine is an interesting and reusable piece. If you want, I can:
- Add an example screenshot to the repo and update README image path.
- Draft the Android JNI wrapper outline to integrate the engine on Android.
- Propose unit tests and a basic CI script to build the fat lib automatically.
