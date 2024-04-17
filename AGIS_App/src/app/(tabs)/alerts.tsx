import { StyleSheet } from 'react-native';

import EditScreenInfo from '@components/EditScreenInfo';
import { Text, View } from '@components/Themed';

export default function Alerts() {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>Alerts</Text>
      <View style={styles.separator} lightColor="#eee" darkColor="rgba(255,255,255,0.1)" />
      <Alert/>
    </View>
  );
}

const Alert = () => {
  return (
    <div>
      <p>All Alerts and Notifications related to the Greenhouse operations will be displayed in this page</p>
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
