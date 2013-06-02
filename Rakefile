require "bundler/gem_tasks"
require "bundler/setup"
require "rspec/core/rake_task"

task default: [:compile, :spec]
RSpec::Core::RakeTask.new(:spec)

task :compile do
  sh 'cd ext/uncle && ruby extconf.rb && make'
end

