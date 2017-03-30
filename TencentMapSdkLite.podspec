#
# Be sure to run `pod lib lint TencentMapSdkLite.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# Any lines starting with a # are optional, but encouraged
#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
s.name             = "TencentMapSdkLite"
s.version          = "2.0.0.00.03"
s.summary          = "This is TencentMapSdk Lite."
s.description      = 'The Map Software develop kit.'
s.homepage         = "https://github.com/TencentSDK/TencentMapSdkLite"
# s.screenshots     = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
s.license          = 'BSD'
s.author           = { "eximpression" => "ex_impression@hotmail.com" }
s.source           = { :git => "https://github.com/TencentSDK/TencentMapSdkLite.git", :tag => s.version.to_s }
# s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

s.platform     = :ios, '7.0'
s.requires_arc = true
s.source_files = 'TencentMapSdkLite/Classes/**/*'
s.vendored_libraries = [
'TencentMapSdkLite/Library/libQMapKitLite.a'
]
s.public_header_files = 'TencentMapSdkLite/Classes/Headers/*.h'
s.resources = 'TencentMapSdkLite/Bundles/SOSOMAPRES.bundle'

s.frameworks = 'SystemConfiguration','UIKit','CoreText','OpenGLES','QuartzCore','CoreGraphics','CoreLocation','CoreTelephony', 'Accelerate','ImageIO'
s.library = 'z','stdc++','stdc++.6.0.9','sqlite3'


end
