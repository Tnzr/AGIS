import React from 'react';
import { View } from 'react-native';
import { LineChart } from 'react-native-svg-charts';

const SensorLinePlot = ({ data }) => {
  return (
    <View>
      <LineChart
        style={{ height: 200 }}
        data={data}
        svg={{ stroke: 'rgb(134, 65, 244)' }}
        contentInset={{ top: 20, bottom: 20 }}
      />
    </View>
  );
};

export default SensorLinePlot;