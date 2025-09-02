// #ifdef DeviceType_BMW_BMS
//   void sendcommand()  //Send Can Command to get data from slaves
//   {  
//     if (timer_BMS_SendCommand.check())
//     {
//         ///////module id cycling/////////

//         if (nextmes == 0xC) {
//           mescycle++;
//           nextmes = 0;
//           if (testcycle < 4) {
//             testcycle++;
//           }

//           if (mescycle == 0xF) {
//             mescycle = 0;

//             if (balancetimer < millis()) {
//               balancepauze = 1;
//               if (debug == 1) {
//                 Serial.println();
//                 Serial.println("Reset Balance Timer");
//                 Serial.println();
//               }
//               balancetimer = millis() + ((60 + 60) * 1000);
//             } else {
//               balancepauze = 0;
//             }
//           }
//         }
//         if (balancepauze == 1) {
//           balancecells = 0;
//         }

//         tx_frame.rtr = 0;
//         tx_frame.id = 0x080 | (nextmes);
//         tx_frame.length = 8;
//         tx_frame.extended = false;
//         if (balancecells == 1) {
//           // tx_frame.data.uint8[0] = lowByte((uint16_t((bms.getLowCellVolt()) * 1000) + 5));
//           // tx_frame.data.uint8[1] = highByte((uint16_t((bms.getLowCellVolt()) * 1000) + 5));
//         } else {
//           tx_frame.data.uint8[0] = 0xC7;
//           tx_frame.data.uint8[1] = 0x10;
//         }
//         tx_frame.data.uint8[2] = 0x00;  //balancing bits
//         tx_frame.data.uint8[3] = 0x00;  //balancing bits

//         if (testcycle < 3) {
//           tx_frame.data.uint8[4] = 0x20;
//           tx_frame.data.uint8[5] = 0x00;
//         } else {

//           if (balancecells == 1) {
//             tx_frame.data.uint8[4] = 0x48;
//           } else {
//             tx_frame.data.uint8[4] = 0x40;
//           }
//           tx_frame.data.uint8[5] = 0x01;
//         }

//         tx_frame.data.uint8[6] = mescycle << 4;
//         if (testcycle == 2) {
//           tx_frame.data.uint8[6] = tx_frame.data.uint8[6] + 0x04;
//         }

//         tx_frame.data.uint8[7] = getcheck(tx_frame, nextmes);
//         CAN0.sendFrame(tx_frame);
//         nextmes++;
//     }
//   }

//   uint8_t getcheck(CAN_FRAME &tx_frame, int id)
//   {
//     unsigned char canmes [11];
//     int meslen = tx_frame.length + 1; //remove one for crc and add two for id bytes
//     canmes [1] = tx_frame.id;
//     canmes [0] = tx_frame.id >> 8;

//     for (int i = 0; i < (tx_frame.length - 1); i++)
//     {
//       canmes[i + 2] = tx_frame.data.uint8[i];
//     }
//     /*
//       Serial.println();
//       for (int i = 0; i <  meslen; i++)
//       {
//       Serial.print(canmes[i], HEX);
//       Serial.print("|");
//       }
//     */
//     return (crc8.get_crc8(canmes, meslen, finalxor[id]));
//   }
// #endif