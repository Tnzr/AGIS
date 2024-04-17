import { StyleSheet } from 'react-native';

import EditScreenInfo from '@components/EditScreenInfo';
import { Text, View } from '@components/Themed';

export default function About() {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>About</Text>
      <View style={styles.separator} lightColor="#eee" darkColor="rgba(255,255,255,0.1)" />
      <Info/>
    </View>
  );
}

const Info = () => {
  return (
    <div style={styles.container}>
      <p><strong>Vision:</strong>aa AGIS aims at automating as much labor from the production of vegetation and mushrooms at an affordable price. AGIS's vision is for Greenhouses to be the next standard household appliance. AGIS will have a minimal and affordable model, along with an upgraded and complete model. AGIS would make sure all conditions are optimal to prevent contamination. In addition, the upgraded model will be able to detect early mycelium contamination and monitor general plant health using Computer Vision and Machine Learning techniques.</p>
      <br/>
      <h2>Areas of Impact</h2><p>
Access to Food:
Around 9 million people die every year from hunger and hunger-caused diseases/illnesses. This is more than from AIDS, malaria, and tuberculosis combined.
<a href='https://www.theworldcounts.com/challenges/people-and-poverty/hunger-and-obesity/how-many-people-die-from-hunger-each-year'>https://www.theworldcounts.com/challenges/people-and-poverty/hunger-and-obesity/how-many-people-die-from-hunger-each-year</a> </p>
<p>
Wasted Food:
One-third of food produced for human consumption is lost or wasted globally. This amount is about 1.3 Billion tons per year, worth Approximately $1 Trillion. All of this food which never reaches the table of the household is enough to feed 2 Billion people. Hundreds of times the amount of people starving and in deteriorating health from lack of access to food.
<a href='https://www.wfp.org/stories/5-facts-about-food-waste-and-hunger'>https://www.wfp.org/stories/5-facts-about-food-waste-and-hunger</a>
</p><p>
Food Insecurity:
The Caribbean economy is consistently impacted by natural disasters. One of the struggles of developing nations in the Caribbean is the consistent consequences of hurricanes. On average, 7 hurricanes are produced a year and erase a significant portion of the Agricultural Industry in those nations. Every time one of these Hurricanes passes they get rid of an estimated 20% of the Nation’s agriculture.
<a href='https://www.datosmundial.com/america/cuba/huracanes.php'>https://www.datosmundial.com/america/cuba/huracanes.php</a>
</p>

    <h2>Contribute</h2>
    <p>Visit our <a href='https://github.com/Tnzr/AGIS'>Github</a></p>
      <p>If you would like to contribute please visit our <a href='https://www.gofundme.com/f/autonomous-greenhouse-irrigation-system-agis'>Fundraiser </a></p>
      <p>Related <a href='https://docs.google.com/spreadsheets/d/1btSftXdY_PI411ZJU9uYeClA3-gr406x3UhjofyOFcw/edit?usp=sharing'>Parts List</a></p>
    
    
    </div>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    width: "70%"
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
