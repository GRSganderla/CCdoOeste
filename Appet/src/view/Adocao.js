import React, { Component } from 'react';
import { Text, View } from 'react-native';
import BackButton from '../controller/BackButton';

export default class Adocao extends Component {
 
  static navigationOptions = () => {
    return {
        headerLeft: <BackButton/>
    };
};
 
  render() {
    return (
      <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
        <Text>Adoção!</Text>
      </View>
    );
  }
}