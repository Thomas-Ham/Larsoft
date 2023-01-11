sample=gamma_vertex_bnblike
stage=reco_cheat

path=/pnfs/sbnd/persistent/users/tham/showers/energy_reco_tech_note/$sample/$stage

echo "Looking in $path..."
echo -n "Number of files found: "; find $path/*/prod*.root -maxdepth 0 -type f | wc -l

# Make list of the files
file_write=${sample}_${stage}.list
# if it already exists, lets remove it 
if test -f $file_write; then
    rm $file_write    
fi


echo "Writing list of files to $file_write..."

for file in $path/*/prod*.root # file type to look for
do
    if [ -f "$file" ]; then
        echo $file >> $file_write
    fi
done
