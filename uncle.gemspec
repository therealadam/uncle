# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'uncle/version'

Gem::Specification.new do |spec|
  spec.name          = "uncle"
  spec.version       = Uncle::VERSION
  spec.authors       = ["Adam Keys"]
  spec.email         = ["adam@therealadam.com"]
  spec.description   = %q{Bindings for UnQLite}
  spec.summary       = %q{Embed a NoSQL database in your Ruby}
  spec.homepage      = "https://github.com/therealadam/uncle"
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]
  spec.extensions    = ['ext/uncle/extconf.rb']

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"
end

