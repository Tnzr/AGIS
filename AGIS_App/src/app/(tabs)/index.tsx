import { StyleSheet } from 'react-native';
import EditScreenInfo from '@components/EditScreenInfo';
import { Text, View } from '@components/Themed';
import DHT_Component from '@/components/DHTDisplay';
import SensorLinePlot from '@/components/SensorLinePlot';
import {SensorDataProvider} from "@/components/SensorDataContext"
import SensorDataWebSocket from '@components/SensorDataWebSocket';


export default function Monitoring() {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>Coming Soon</Text>
      <View style={styles.separator} lightColor="#eee" darkColor="rgba(255,255,255,0.1)" />
      <Todo/>
      {/* <SensorDataProvider>
        <SensorDataWebSocket host="192.168.254.157" port={8080}>
            
        </SensorDataWebSocket>
      </SensorDataProvider> */}
      <DHT_Component host="192.168.254.157" port={8080} />
      
    </View>
  );
}

const Todo = () => {
  return (
    <div>
      <h1>TODO:</h1>
      <ul>
        <li>Review: <a href='https://www.youtube.com/watch?v=z-I-r3PX2lU'>Watch ESP32 Web Server Tutorial</a></li>
        <li>Create React Monitoring Page</li>
        <li>Create ESP32 WebServer</li>
        <li>Integrate</li>
      </ul>
    </div>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
  },
  separator: {
    marginVertical: 30,
    height: 1,
    width: '80%',
  },
});
