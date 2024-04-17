import React, { useEffect, useState } from "react"
import { Text, View } from '@components/Themed';
import { StyleSheet, TextInput } from 'react-native';
import systemSettings from "../../assets/settings/system_settings"



const SettingOption = ({key, name, value}) => {
    const [inputValue, setInputValue] = useState(value);
    const handleInputChange = (text) => {
        console.log(systemSettings);
        setInputValue(text);
    }

    return (
        <View style={styles.settingItem}>
            <Text>{name}</Text>
            <TextInput style={styles.settingValue} value={inputValue} onChangeText={handleInputChange}/>
        </View>
    );
};

class SettingsPanel extends React.Component {
    constructor(props){
        super(props);
        
        this.state = {
            showSettings: true
        }
    }

    toggleSettings = () => {
        this.setState(prevState => ({
            showSettings: !this.state.showSettings,
        }))
    }

    render() {
        const {showSettings}=this.state;
        const {category, onChange} = this.props;
        console.log(category.setting);
        return (
            <div className={category.name} style={styles.settingsList}>
                <h1 onClick={this.toggleSettings}
                className="category-header">{category.name}</h1>
                {showSettings ? (
                    <div className={category.name} style={styles.settingItem}>

                    {category.settings.map((setting) => (
                    <SettingOption 
                        key={setting.name}
                        name={setting.name+":\t"}
                        value={setting.value}
                        onChange={onChange}
                        />
                    ))}
                    </div>
                    
                ): null}
            </div>
        )
    }
}

class SettingsMenu extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
          active: true,
        };
      }

      toggleCategory = (categoryName) => {
        this.setState((prevState) => ({
          active: !prevState.active,
        }));
        const { settings, onChange } = this.props;
        const updatedSettings = settings.map((category) => {
          if (category.name === categoryName) {
            this.state.active = !this.state.showSettings;
            return category;
          }
          return category;
        });
        // Update settings state
        onChange(categoryName, categoryName, updatedSettings);
      };
    
      render() {
        const { settings , onChange} = this.props;
        return (
          <div className="settings-panel">
            {settings.map((category) => (
                    <SettingsPanel category={category} onChange={onChange}/>
            ))
            }
          </div>
        );
      }
    }

const Setting = () => {
    // Initialize settings state with default values from the JSON data
  const [settings, setSettings] = useState(systemSettings);

  // Function to handle setting changes
  const handleSettingChange = (categoryName, settingName, value) => {
    setSettings((prevSettings) => {
      const updatedSettings = prevSettings.map((category) => {
        if (category.name == categoryName) {
          return {
            ...category,
            settings: category.settings.map((setting) => {
              if (setting.name == settingName) {
                return { ...setting, value };
              }
              return setting;
            }),
          };
        }
        return category;
      });
      // Save updated settings to local storage
      localStorage.setItem('../../assets/settings/system_settings', JSON.stringify(updatedSettings));
      return updatedSettings;
    });
  };

  // Load settings from local storage on initial render
  useEffect(() => {
    const savedSettings = JSON.parse(String(localStorage.getItem('../../assets/settings/system_settings')));
    if (savedSettings) {
      setSettings(savedSettings);
    }
  }, []);

  return (
    <View>
      <SettingsMenu settings={settings} onChange={handleSettingChange} />
    </View>
  );
};


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
    settingName: {
        flex: 1,
        padding: 20,
    },
    settingValue: {
        flex: 1,
        borderColor: "#000",
        textAlign: "right",
        justifyContent: "flex-end",
        marginLeft: 10,
    },
    settingItem: {
        // display: "none",
        alignItems: "stretch",
        justifyContent: "space-between",
        padding: 8,
        borderColor: "#000"
        // borderBottomColor: "#ccc",
        // borderBottomWidth: 1,
    },
    settingsList: {
        display: "flex",
        flexDirection: "column"
    }
  });

// export default Setting;
