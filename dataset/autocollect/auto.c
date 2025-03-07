#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

const char *binaryFiles[] = {
    "./bin/f72babf978d8b86a75e3b34f59d4fc6464dc988720d1574a781347896c2989c7.bin",
    "./bin/f487b23309808e468889baf10c852284b7833b8ac06fd405d1b19abafc8e17fb.bin",
    "./bin/ef11c120fab2129fce6dddb8b007102ef98281e11864386ff09c179c58d1dfe0.bin",
    "./bin/ee4a196838ecd12aec77832973b52ead73d751a25da50e96e3146c0b373bb610.bin",
    "./bin/ed1e49cb05c375cc1149c349880ed077b6ee75cb7e5c6cae9cbd4bd086950c93.bin",
    "./bin/eb1081f1a300516bd134b229141e9b9c31d4bc53e6cd4ba0def6135f9b15179b.bin",
    "./bin/e627aff93c1e095786b5a5248425ec62c1ea8b049d487cfa6e9cfdf2a0ddbd7b.bin",
    "./bin/dec628d38b1cece3a980e56813cc3000bdc4d92a08bdf7892961655f1e2e91dd_unpacked_352136aeeec4616618a1982cf5b7cb736ac96249196952e6625021da007bb409.bin",
    "./bin/dec628d38b1cece3a980e56813cc3000bdc4d92a08bdf7892961655f1e2e91dd.bin",
    "./bin/dd803990ea400619668840343c25672b4a2c5c0e0622958e2cdf8be95b6baaab_unpacked_d58704dd815acaba68c9f903d758272e351db016eb5b678a76e6c6c1d1299f32.bin",
    "./bin/dd803990ea400619668840343c25672b4a2c5c0e0622958e2cdf8be95b6baaab.bin",
    "./bin/dd5b4de5a1c68aad5a2efb08db55cb3e09f8ddffc19c95c1ecf9d06c6edf2d40_unpacked_40d2a9f883bf3809fd4fd59e56be4a90d53879ec4145bebf1d7b8ac9c0b7c2ca.bin",
    "./bin/dd5b4de5a1c68aad5a2efb08db55cb3e09f8ddffc19c95c1ecf9d06c6edf2d40.bin",
    "./bin/dd31b774397c6e22375d4f2fe26e38e82ae164bc73cf58314b18b8eed26802f0_unpacked_d5ce80121f274fea8066b4f3e99f93fc0767783aa6c658252b7bbaea7648d196.bin",
    "./bin/dd31b774397c6e22375d4f2fe26e38e82ae164bc73cf58314b18b8eed26802f0.bin",
    "./bin/d54157bb703b360bb911363d9bb483a2ee00ee619d566d033a8c316f06cf26cc.bin",
    "./bin/d42090b274d285e759de296239bd7b8e5d97270b2d2ae189aed80e68ba82b591_unpacked_2d5de0dfa05c2a2649a4537b3f935f3ab2c029eeb3a07ab33592611388c845aa.bin",
    "./bin/d42090b274d285e759de296239bd7b8e5d97270b2d2ae189aed80e68ba82b591.bin",
    "./bin/c7e136001338f2921fc6bbd67e1de8d4a5098b02eab55a47aa3bff2fa7ad8b77_unpacked_dfeafb94f29f4e5f0f98a945f0d7ca352ea5b8b05628c634a5a3114a0bb164b2.bin",
    "./bin/c7e136001338f2921fc6bbd67e1de8d4a5098b02eab55a47aa3bff2fa7ad8b77.bin",
    "./bin/c55706ddbfdcecf77f225e711463f50d7da127818ee93a6be10836e4c1662393_unpacked_46276eddb4054209096af4f115965aeef466494ea34a624e4eae6c9d130962b7.bin",
    "./bin/c55706ddbfdcecf77f225e711463f50d7da127818ee93a6be10836e4c1662393.bin",
    "./bin/bf2c450d4d3519de51fbd31def04a0e6786e13a568ddefcaa62d812cc72ffc4c_unpacked_3e66b5216159e06d4ff1e94662d34c5bce4bf4f61bb40dfba11c6cec9b29d742.bin",
    "./bin/bf2c450d4d3519de51fbd31def04a0e6786e13a568ddefcaa62d812cc72ffc4c.bin",
    "./bin/beaa0639a67f7fc7937a100f01a550ecb8c8b608251f4d02a97d9a0a15de1304_unpacked_322ccf40134f3b229858817e0fe3b7b9e40cc9f94fabd71b1eeb1b173b6b5955.bin",
    "./bin/beaa0639a67f7fc7937a100f01a550ecb8c8b608251f4d02a97d9a0a15de1304.bin",
    "./bin/bcb02047374196acdf0285a656a8d378cecd6115c403d0bc9f743b4e3ffd6fed_unpacked_17fbc8e10dea69b29093fcf2aa018be4d58fe5462c5a0363a0adde60f448fb26.bin",
    "./bin/bcb02047374196acdf0285a656a8d378cecd6115c403d0bc9f743b4e3ffd6fed.bin",
    "./bin/b2e51777c7993ce58f5e1afd3d33efbaae19222099be745f229b44028766dabc.bin",
    "./bin/b1a5a0ea66245ba5f3c323cf411960079568d2c2891e680e8e0abcffb8f651a1.bin",
    "./bin/af7c5617a89c40aac9eb2e573a37a2d496a5bcaa9f702fa919f86485e857cb74.bin",
    "./bin/af7c5617a89c40aac9eb2e573a37a2d496a5bcaa9f702fa919f86485e857cb74_unpacked_896fde201defea3e0a832026e5a015fe3ced0aa6ce11cfbb541bf3a423d37201.bin",
    "./bin/acbb4f3f9a13845de0c1c23f06dcb554817e610318e57718e63ce6a57af4911c.bin",
    "./bin/a999d7f95af4084b1e4276ee329e9b466c4d88a14cfc87007587d18a4a6c9f8a_unpacked_8f921a59fd92e455d518ec3f6dbde6d72d60426f1b2147e07285d30fccf0745a.bin",
    "./bin/a999d7f95af4084b1e4276ee329e9b466c4d88a14cfc87007587d18a4a6c9f8a.bin",
    "./bin/a34ae92c904b60ed7c1dc437493d1b086a828d25c52e5409d2c7b79b880db42f.bin",
    "./bin/a22c2a6c2fdc5f5b962d2534aaae10d4de0379c9872f07aa10c77210ca652fa9.bin",
    "./bin/9d85b4e7202521d435a871b7de5f8affd30603687cf6e6f39f1420e9223b2bea_unpacked_8bc38b6764e6d6ebab4a93a2c22485a75dfb2f7dcf74c7b7b420e6c7dfadc7bd.bin",
    "./bin/9d85b4e7202521d435a871b7de5f8affd30603687cf6e6f39f1420e9223b2bea.bin",
    "./bin/9c9b7da616239290db831a9305e1a46d45c112c761deaea5ed4c36aea7433891_unpacked_59737717f797d8c238142573bc0c9bfff7b92d069ea3d6be308e8dc7a9bd000f.bin",
    "./bin/9c9b7da616239290db831a9305e1a46d45c112c761deaea5ed4c36aea7433891.bin",
    "./bin/9b2023a0e22f22860a7a46a67c9eba2c4831db66244603fd961fbb5c38b55272_unpacked_6eaabf75f284438f371dae340e4c4215a7f18f681f7602fbc0d857fa7b6783e3.bin",
    "./bin/9b2023a0e22f22860a7a46a67c9eba2c4831db66244603fd961fbb5c38b55272.bin",
    "./bin/97106c8ca7af1cce73527e8cee2db6a923b257dc8b741ef3e05ecc52468413cc_unpacked_631621e9bbd2ca68a76ae7bf971fcdb85c856d2db1a74696dd6822f8a7fa35a9.bin",
    "./bin/97106c8ca7af1cce73527e8cee2db6a923b257dc8b741ef3e05ecc52468413cc.bin",
    "./bin/95f9faf8a4ef5db4a3e60d577287e18fbbe32336a3b98c256da601645b674c74_unpacked_a392af98e2fe54d00c4b7f58042cffc0d8bd947f1e487a74f6caea99cc876575.bin",
    "./bin/95f9faf8a4ef5db4a3e60d577287e18fbbe32336a3b98c256da601645b674c74.bin",
    "./bin/945cd9e2d05e525417d48c3b18f8b2b953f468ff2f26ddeec4f456812719922a_unpacked_8c8ee06a38dab2265181923e4bd4d71017030a0bc8e2ad5e3a0da64a789af14f.bin",
    "./bin/945cd9e2d05e525417d48c3b18f8b2b953f468ff2f26ddeec4f456812719922a.bin",
    "./bin/89bc80a0bca059535741063ea882c1602cb369af7deea0e45e982b33faa10a68_unpacked_427ccf76c6aa249521f0d8fcea9f3a20cff499abd5a2048d03574acc2f6a13dd.bin",
    "./bin/89bc80a0bca059535741063ea882c1602cb369af7deea0e45e982b33faa10a68.bin",
    "./bin/848ed7e90c767e7ab2b1a93f9b8ca9c41eb02c3c76bf8b7dfd806fe26c1f431e_unpacked_875f0740540275a62b311fd232f4144f99e3423ca55381599e4badd40d47dba3.bin",
    "./bin/848ed7e90c767e7ab2b1a93f9b8ca9c41eb02c3c76bf8b7dfd806fe26c1f431e.bin",
    "./bin/8353823b0dc71e1feec1a2ba5e509966d5dae7f5105489c1e628baa73b314d76_unpacked_5f80945354ea8e28fa8191a37d37235ce5c5448bffb336e8db5b01719a69128f.bin",
    "./bin/8353823b0dc71e1feec1a2ba5e509966d5dae7f5105489c1e628baa73b314d76.bin",
    "./bin/81e5beaf5683b92b1a238a909805bd02298830dc90d383facdebdb170230ec34_unpacked_0cca26dc3b4e09ce7d9c9939d9c56128d611ba280729a98735abb5e66a27af58.bin",
    "./bin/81e5beaf5683b92b1a238a909805bd02298830dc90d383facdebdb170230ec34.bin",
    "./bin/7ff5f2b3145d1e54a84f5bcc13ae6838baac2d6c20951d19608166833753d96f_unpacked_658bd41a38234362e635f0b7497d84a13ab38a8a383924803cc0fa0c931c2193.bin",
    "./bin/7ff5f2b3145d1e54a84f5bcc13ae6838baac2d6c20951d19608166833753d96f.bin",
    "./bin/7a546057a47ee02f6436e51d6d61f1b63c525307f9b5076a8edfe2cf4ae68769_unpacked_21f579ba681fb0f6c6ce5f816d60a8267943b87d451a50e04443dfaadbc3bdce.bin",
    "./bin/7a546057a47ee02f6436e51d6d61f1b63c525307f9b5076a8edfe2cf4ae68769.bin",
    "./bin/798d1292b97eddc2b92a017f2599cf3f3e26e0695e2c2a27b897a483b32d9753_unpacked_1ebfd0b7857696b057c0f62a71c1d73956200ed70a741e8cd9f957ef6b29bfd6.bin",
    "./bin/798d1292b97eddc2b92a017f2599cf3f3e26e0695e2c2a27b897a483b32d9753.bin",
    "./bin/78f92857e18107872526feb1ae834edb9b7189df4a2129a4125a3dd8917f9983.bin",
    "./bin/7579f96024d9ad50f490b017def89a825358eabb85f55959091e26eb863ec19b.bin",
    "./bin/75253aa48ff1db29e291d6acfe5da2832a4e6e0481950a6d17cea7e92d8a2336.bin",
    "./bin/72483800c412e2204731b12c9d8fff1bc84f7af8f0b258299bb4f091a57ab23a.bin",
    "./bin/720341984c842070dcc925cb47127aba35e16971cf7d532cc2efb24b98d56c93_unpacked_7e765c12a391308879f1e6b57bf6ae87c0fd0e8d6e0207954cc3a41fd387fda9.bin",
    "./bin/720341984c842070dcc925cb47127aba35e16971cf7d532cc2efb24b98d56c93.bin",
    "./bin/6f2825856a5ae87face1c68ccb7f56f726073b8639a0897de77da25c8ecbeb19.bin",
    "./bin/6abdd9effedb3ecc70326493f3676d3c6bbd0d3cc0d8d172885b344a3fa07e27.bin",
    "./bin/67f03f3065ec012cd8853e9d1b11cb441741910a24cb23ea652fb63d7219ebaa_unpacked_18bc08cccf7ba713c7cc734547dca9776fcee9459c0b4e9549bb8b9923d21732.bin",
    "./bin/67f03f3065ec012cd8853e9d1b11cb441741910a24cb23ea652fb63d7219ebaa.bin",
    "./bin/6750e584ad0c21588e0add09c6ebe0cc9affe1673ac848b1761359170cf08bb7.bin",
    "./bin/65296e0307167af398fec4ac4282832cf7096c1b85cb4cf5d75fdda63ad438ca.bin",
    "./bin/5fc4c90fae41a53ef41cac0ef2c0c7f4076d8ac3e49bf71daaebe584eb03ea91_unpacked_0bca38101bc4014e0946f789a12ee4b4da69e5bfb1756262dd1c30e759a42322.bin",
    "./bin/5fc4c90fae41a53ef41cac0ef2c0c7f4076d8ac3e49bf71daaebe584eb03ea91.bin",
    "./bin/5f5d599d4d0f9149440a6f813c6db3759d4fdbf7abe991c3af3aa59dc8c4027f_unpacked_c42e5fae2abfdf02ea08676d2321f139c21e5ac27a49a8bfe55c2e4304d0278e.bin",
    "./bin/5f5d599d4d0f9149440a6f813c6db3759d4fdbf7abe991c3af3aa59dc8c4027f.bin",
    "./bin/5f1d1141da3fe3261edf03c6be1625fe8c8443bdb5381252658100b4f296df6e_unpacked_0d3b0dc5ea6643d36d745fcaa177eba88200b2b16596111e140f59092070594f.bin",
    "./bin/5f1d1141da3fe3261edf03c6be1625fe8c8443bdb5381252658100b4f296df6e.bin",
    "./bin/544d20fc286d0803dee86a9c34b4c348333e320a4e33fd2730079701cb6e108f_unpacked_d50864f13378b333784f7469df98ef2ea438489ccf0649622897a7712a9c18f8.bin",
    "./bin/544d20fc286d0803dee86a9c34b4c348333e320a4e33fd2730079701cb6e108f.bin",
    "./bin/5208cda8463eee0ac2cf0273dcd4036aa1e2be0de2c45b4ffd71e4c92bac3f2b_unpacked_77a9f3d4f498c8a84e09c89fd75d98eea31954cc17d948b876c00c638c95a7b6.bin",
    "./bin/5208cda8463eee0ac2cf0273dcd4036aa1e2be0de2c45b4ffd71e4c92bac3f2b.bin",
    "./bin/4fd37fa6ccf027e11409e3ca3b8109b2830cb3d7842303e67e6d0c087ae1b419_unpacked_61e358f338d9fcb41f6fcebced95279614309f80c8ec2e70e5bc991f185f4d6f.bin",
    "./bin/4fd37fa6ccf027e11409e3ca3b8109b2830cb3d7842303e67e6d0c087ae1b419.bin",
    "./bin/4d6e5c861f04ed4a14195e29e60f6efba03c05bc213c3a6cffe0f0116a013e5b_unpacked_2d9c1446cd174feb3733fc4595d326424555a40b2e6e2f56e7bee1c5a7c9a22d.bin",
    "./bin/4d6e5c861f04ed4a14195e29e60f6efba03c05bc213c3a6cffe0f0116a013e5b.bin",
    "./bin/4484abf66bca5df43285dfa9980bf4d81725af66c0b8ed3129d3a58fe1db5043.bin",
    "./bin/428340a0695393a0cec55513e700a479e252d9b034f27f80a29da3ac99afa459.bin",
    "./bin/3ea2df69b99f78fc0768ecf8190293f2b277b6de6e7b8e668f40b8a4910df17c_unpacked_d3196b0b4767e86bf7e9e47722a5f733129c16f81f0ccbe5f822bdcfd778ca16.bin",
    "./bin/3ea2df69b99f78fc0768ecf8190293f2b277b6de6e7b8e668f40b8a4910df17c.bin",
    "./bin/3d2e8bd1f02486b305d01fcc54091c84500409c454a048dad650f1605df6fd9a.bin",
    "./bin/3a6b7ee9503a90c5c5735c2867586b0dfc38e1e148d7f6d902f13e298362fc45_unpacked_6ed86acdada24aa3b902a69cb9467b91e934a241776f78049348c90c16ea1496.bin",
    "./bin/3a6b7ee9503a90c5c5735c2867586b0dfc38e1e148d7f6d902f13e298362fc45.bin",
    "./bin/2fa5832e8b73a6f585f937f396d7b430d35d23ea607d10649a40989068c6c923_unpacked_1a7bed94e83967740294bd5a4d67c2d2650343162869f27fb7dbcc2654848a52.bin",
    "./bin/2fa5832e8b73a6f585f937f396d7b430d35d23ea607d10649a40989068c6c923.bin",
    "./bin/296d3d3ed5feeda7f6d99adc9da2566cb6c460194066acccac941a7b09bedfc3_unpacked_d93afaecbf25e4fa25d345afa408f1fa6e329bfbcd566b662916328fdd155fd4.bin",
    "./bin/296d3d3ed5feeda7f6d99adc9da2566cb6c460194066acccac941a7b09bedfc3.bin",
    "./bin/22ef90a2b3c23d3c890358fff4ec1210e4ceaaf46d8bef525294151b0e88ce15_unpacked_feb38d0bc7b6d676337241f74ffdad97d9d03736c2f6b12a8047d9a93a924f9b.bin",
    "./bin/22ef90a2b3c23d3c890358fff4ec1210e4ceaaf46d8bef525294151b0e88ce15.bin",
    "./bin/1dd2c66843fcf5512b4dda518c2d5010edf06ab701f0380777b1b305ce9c98b0_unpacked_47183b14ed24978643de4697abe917847831b1560256ddd76e44e918a6181fd8.bin",
    "./bin/1dd2c66843fcf5512b4dda518c2d5010edf06ab701f0380777b1b305ce9c98b0.bin",
    "./bin/1c91ed47c3c0baa74fa15c9b02330701dd02fc1e9b44963e1fe9a650ef7b78ef_unpacked_9df43de4920699bd51d4964b681bd2ce8315b189b812f92084f7c3e423610b2f.bin",
    "./bin/1c91ed47c3c0baa74fa15c9b02330701dd02fc1e9b44963e1fe9a650ef7b78ef.bin",
    "./bin/1a63f7a38c7f5a5cc770246c958aea70ea95bcafac1bad92d2d524f4fe24c1ca_unpacked_62ba664a95b3ca00e7a71fe6aa4a979c5a50f16a62cf72830af13bec7edb1da4.bin",
    "./bin/1a63f7a38c7f5a5cc770246c958aea70ea95bcafac1bad92d2d524f4fe24c1ca.bin",
    "./bin/18a877f11f2ba2d7ae05ee8644a5cbd687282df4010dd0cb7680aec2e00d98ce_unpacked_f640c11ebbedb71a03e94fbdde8d8944206f15a9641bcdad1f13ba8dfe507a2c.bin",
    "./bin/18a877f11f2ba2d7ae05ee8644a5cbd687282df4010dd0cb7680aec2e00d98ce.bin",
    "./bin/163ef20a1c69bcb29f436ebf1e8a8a2b6ab6887fc48bfacd843a77b7144948b9_unpacked_ba518af59262e878d31c71020ebfcbd50dfadf1e7c47a340003c80284681794b.bin",
    "./bin/163ef20a1c69bcb29f436ebf1e8a8a2b6ab6887fc48bfacd843a77b7144948b9.bin",
    "./bin/1489c404a110149b66476e0f41317770f0291da64a0d4b39f28900ccaf4d30f2.bin",
    "./bin/1384790107a5f200cab9593a39d1c80136762b58d22d9b3f081c91d99e5d0376_unpacked_afb6ec634639a68624c052d083bbe28a0076cd3ab3d9a276c4b90cb4163b8317.bin",
    "./bin/1384790107a5f200cab9593a39d1c80136762b58d22d9b3f081c91d99e5d0376.bin",
    "./bin/0c13b3528088c308ac28971fba93939c66da2eabef66a4d3790c0b1817221535_unpacked_b8fe253c43a120312376aa1b027823c1be3bac7667fcc649447d36b24d7d9951.bin",
    "./bin/0c13b3528088c308ac28971fba93939c66da2eabef66a4d3790c0b1817221535.bin",
    "./bin/0b6037eadb03feed5eb6c67ef4a68e80c64cf619670c6e3187ba076a017c4c85_unpacked_d429ad4d47ec2491f471c685ac023c77493e96086b819a63ebee2fa48c596090.bin",
    "./bin/0b6037eadb03feed5eb6c67ef4a68e80c64cf619670c6e3187ba076a017c4c85.bin",
    "./bin/04c1fe3bf04ebf65d38987f3d1a728684970e88503fa075e2d0b8bbbe98a14cb_unpacked_f8472088ed5f5d2ce5be330dac60aec446173fc84a565ff7831e6b07060c55c0.bin",
    "./bin/04c1fe3bf04ebf65d38987f3d1a728684970e88503fa075e2d0b8bbbe98a14cb.bin",
    "./bin/1b2909eda77c14b559b06a68a794868989b7e38c9ca185a3180c63e5c38622b5_unpacked_f425fa120bc1b3926ed92ed5cec74898f1d40c3059ae443f816a9e10a2699f80.bin",
    "./bin/1b2909eda77c14b559b06a68a794868989b7e38c9ca185a3180c63e5c38622b5.bin"
};

const int numBinaryFiles = sizeof(binaryFiles) / sizeof(binaryFiles[0]);

const char *programPath = "../syscall/.syscall";

// killall
void executeKillall(const char *binaryName) {
    char command[256];
    for (int i = 0; i < 5; i++) {
        snprintf(command, sizeof(command), "killall -e %s", binaryName);
        system(command);
    }
}

// clearing schedule
void clearCrontab() {
    system("crontab -r");
}

// dataset labeling
void renameDataset() {
    static int counter = 1;
    char oldName[] = "../syscall/DATASET/Malware/test";
    char newName[256];
    snprintf(newName, sizeof(newName), "../syscall/DATASET/Malware%04d", counter++);
    rename(oldName, newName);
}

void waitForChild(pid_t pid) {
    int status;
    while (waitpid(pid, &status, 0) != pid);
}

int main() {
    for (int i = 0; i < numBinaryFiles; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Execute cryptojacker
            execl(binaryFiles[i], binaryFiles[i], NULL);
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            // Execute eBPF monitor
            pid_t programPid = fork();
            if (programPid == 0) {
                char arg[5];
                strncpy(arg, binaryFiles[i] + 6, 4);
                arg[4] = '\0';
                execl(programPath, programPath, arg, NULL);
                perror("execl failed");
                exit(1);
            }

            waitForChild(programPid);
            executeKillall(binaryFiles[i]);
            clearCrontab();
            renameDataset();
            waitForChild(pid);
        } else {
            perror("fork failed");
            exit(1);
        }
        printf("dataset has been created: %04d\n", (i + 1));
    }

    return 0;
}