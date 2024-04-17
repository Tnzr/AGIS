import React, { createContext, useContext, useState} from "react";

const SensorDataContext = createContext();

export const useSensorData = () => useContext(SensorDataContext);

export const sensorDataProvider = ({children}) => {
    const [sensorData, setSensorData] = useState(null);

    const updateSensorData = (newData) => {
        setSensorData(newData);
    };

    return (
        <SensorDataContext.Provider value={{sensorData, updateSensorData}}>
            {children}
        </SensorDataContext.Provider>
    )
}