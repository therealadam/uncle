require 'spec_helper'

describe Uncle do

  before { `rm test.db*` }
  it "creates a DB" do
    db = Uncle::DB.new('test.db')
    db.close
    expect(File.exists?('test.db')).to be_true
    expect(File.read('test.db').length).not_to eq(0)
  end

end
