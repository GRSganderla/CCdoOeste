import React from 'react';
import Adocao from './Adocao';
import Vaquinha from './Vaquinha';
import Discussao from './Discussao';
import { Component} from 'react';
import { Container, Tab, Tabs, StyleProvider} from 'native-base';
import { Button, Text, View, Icon } from 'react-native';
import { TabBarTop} from 'react-native';
import { StyleSheet } from 'react-native';
import HamburgerIcon  from '../controller/sidebaricon';

class Perdidos extends Component {

  static navigationOptions = () => {
    return {
        headerLeft: <HamburgerIcon />
    };
  };
  
  render() {
    return (
        <Container>
            <Tabs>
                <Tab
                heading='Green Tab'>
                    <View style={styles.container}>
                        <Text style={styles.title}>Green Screen</Text>
                    </View>
                </Tab>
                <Tab heading='Tab 2'>
                </Tab>
                <Tab heading='Tab 3'>
                </Tab>
            </Tabs>
        </Container>
    );
}
}
const styles = StyleSheet.create({
container: {
flex: 1,
justifyContent: 'center',
alignItems: 'center',
backgroundColor: 'green',
},
title: {
fontSize: 20,
textAlign: 'center',
margin: 10,
}
});

export default Perdidos;

/*export default createAppContainer(createBottomTabNavigator(
{
  Perdidos: { screen: Perdidos},
  Adocao: { screen: Adocao},
  Vaquinha: { screen: Vaquinha},
  Discussão: { screen: Discussao},
},
{
  tabBarOptions: {
    activeTintColor: 'tomato',
    inactiveTintColor: 'gray',
  },
}
));*/