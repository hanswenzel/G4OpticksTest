for PARTICLE in pi+
do
    for PHYSLIST in FTFP_BERT_HP
    do
	for ENERGY  in 1. 2. 5. 10. 20. 50. 
	do
	    SCRIPT=scripts/${PARTICLE}_${PHYSLIST}_${ENERGY}GeV.C
	    echo $SCRIPT
	    echo "TSystem ts;" > $SCRIPT
	    echo 'gSystem->Load("/data2/wenzel/gputest10/G4OpticksTest-install/bin/libG4OpticksTestClassesDict");' >> $SCRIPT
	    echo 'TChain ch("Events");' >> $SCRIPT
	    ls -1 PBWO_${PHYSLIST}_${PARTICLE}_${ENERGY}*_hits.root | sed 's/PBWO/ch.Add("PBWO/g' | sed 's/root/root");/g' >> $SCRIPT
	    FILENAME=merged/PBWO_${PHYSLIST}_${PARTICLE}_${ENERGY}GeV_allhits.root
	    echo 'ch.Merge("'$FILENAME'");' >> $SCRIPT
	    /data2/wenzel/root_install/bin/root < ${SCRIPT}
	done
    done    
done

for PARTICLE in pi+
do
    for PHYSLIST in  FTFP_BERT_HP
    do
	for ENERGY  in   1. 2. 5. 10. 20. 50.    
	do
	    mv PBWO_${PHYSLIST}_${PARTICLE}_${ENERGY}*_hits.root	split
	done
    done    
done 
