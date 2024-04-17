import { useEffect } from "react";
import { useSensorData } from "./SensorDataContext";

export const SensorDataWebSocket = ({host, port}) => {
    const {updateSensorData} = useSensorData();



    useEffect(()=>{
        const socket = new WebSocket(`ws://${host}:${port}/ws`);
        setWs(socket);

        socket.onopen = () => {
            console.log("Connected to ESP32 WebSocket");
        };

        socket.onmessage = (event) => {
            const data = JSON.parse(event.data);  
            // console.log("\nParsed: "+data);          
            setData(data);
        };

        socket.onclose = ()=> {
            console.log("Disconnected from ESP32 WebSocket");
        };

        return () => {
            socket.close();
        };
    }, [host, port, updateSensorData]);
    return null
    
};