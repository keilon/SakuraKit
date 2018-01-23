Pod::Spec.new do |s|
  s.name             = "SakuraKit"
  s.version          = "0.0.6"
  s.summary          = "Sakura iOS sdk."
  s.homepage         = "https://github.com/keilon/SakuraKit"
  s.license          = 'MIT'
  s.author           = { "keilon" => "wangxiang_7@hotmail.com" }
  s.source           = { :git => "https://github.com/keilon/SakuraKit.git", :tag => s.version.to_s }
  s.platform     = :ios, '10.0'
  s.requires_arc = true
  s.frameworks = 'Foundation'
  s.vendored_frameworks = 'SakuraKit.framework'
end
