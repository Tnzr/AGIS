// import React, { useEffect, useState } from "react";
// import { Text, View } from '@components/Themed';
// import { StyleSheet, TextInput } from 'react-native';
// import systemSettings from "../../assets/settings/system_settings"

// const IMUComponent = () => {
//     const [ws, setWs] = useState(null);
//     const [data, setData] = useState('');

//     useEffect(()=>{
//         const socket = new WebSocket("ws://esp32-ip: port");

//         if(!socket) return;
//         socket.onopen = () => {
//             console.log("Connected to ESP32 WebSocket");
//         };

//         socket.onmessage = (event) => {
//             setData(event.data);
//         };

//         socket.onclose = ()=> {
//             console.log("Disconnected from ESP32 WebSocket");
//         };
//         setWs(socket);

//     }, [ws]);

//     return (
//         <View>
            
//         </View>
//     )
// }
// // imu format : acc, mag, gyro
// const IMU = ({imu_packet}) => {
//     return (
//     <div>
//         {imu_packet.map((metric) => {
//             <MetricList name={metric.name} data={metric.data}/>
//         })}
//     </div>)
// };

// const MetricList = (name, data) => {
//     return (
//         <div>
//             <h2 className={name+"-header"}>{name}</h2>
//             <ul>
//                 {data.map((metric) => (
//                     <li>
//                         {metric.name}={metric.value}
//                     </li>
//                 ))}
//             </ul>
//         </div>
//     )
// }

// export default IMUComponent;