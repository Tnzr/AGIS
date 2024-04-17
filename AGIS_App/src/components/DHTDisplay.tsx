import React, { useEffect, useState } from "react";
import { Platform, StyleSheet } from 'react-native';

const DHT_Component = ({host, port}) => {
    const [ws, setWs] = useState(null);
    const [data, setData] = useState(null);

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
    }, [host, port]);  
    console.log(data);
    if (!data || !data.DHT_Sensor || !Array.isArray(data.DHT_Sensor)) {
        return (
            <div>
                <h2>Sensor Stats</h2>
                <p>Data is not available</p>
            </div>
        );
    } else {
        return (
            <div style={styles.container}>
                <h2 style={styles.title}>Sensor Stats  DHT1</h2>
                    {data.DHT_Sensor.map((metric, index)=>(
                        
                            <div key={metric.id}>
                                <p>
                                    {metric.title}:  {metric.value ? `${metric.value}` : 'Loading...'}
                                </p>
                            </div>
                    ))}
            </div>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        backgroundColor: "#f0f0f0",
        maxHeight: "30%",
        padding: 20,
        borderRadius: 10,
        borderWidth: 2,
        borderColor: "#ccc",
        // flex: 1,
        alignItems: "flex-start",
        // alignSelf: "flex-start",
        justifyContent: 'center',
        margin: 10,
        marginBottom: 10,
    },
    title: {
        fontSize: 18,
        fontWeight: 'bold',
        marginBottom: 10,
        color: '#333',
    },
    sensorItem: {
        flexDirection: "row",
        justifyContent: "space-between",
        alignItems: "center",
        marginBottom: 5,
    },
    sensorLabel: {
        fontSize: 16,
        color: "#555",
    },
    sensorValue: {
        fontSize: 16,
        fontWeight: 'bold',
        color: '#222',
      },
    separator: {
    marginVertical: 30,
    height: 1,
width: '80%',
    },
  });
export default DHT_Component;