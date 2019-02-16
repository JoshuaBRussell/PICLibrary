OUT_FILE = "test/simulation/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE
IO.popen("/usr/bin/mplab/bin/mdb.sh test/simulation/sim_instructions_mdb.txt")

sleep 10
if File.exists? OUT_FILE
    file_contents = File.read OUT_FILE
    #file_contents.gsub!("\n", "")
    puts file_contents
end
