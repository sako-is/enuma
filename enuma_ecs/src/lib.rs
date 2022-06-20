/* Copyright 2022 Said Isazada 
*  Licensed under the Apache License, Version 2.0 (the "License"); 
*  you may not use this file except in compliance with the License. 
*  You may obtain a copy of the License at 
*      http://www.apache.org/licenses/LICENSE-2.0 
*  Unless required by applicable law or agreed to in writing, software 
*  distributed under the License is distributed on an "AS IS" BASIS, 
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and 
*  limitations under the License. 
*/

use std::collections::HashMap;
use std::fmt::Debug;

#[derive(Debug)]
pub struct Entity {
    name:       String,
    components: Vec<Component>
}

impl Entity {
    fn new(_: &Self, name: String, components: Vec<Component>) -> Self {
        Self { name, components }
    }
}

#[derive(Debug)]
struct Component {
    properties: HashMap<String, Box<dyn Debug>>
}

impl Component {
    fn new(_: &Self, names: Vec<String>, parts: Vec<Box<dyn Debug>>) -> Self {
        let mut properties = HashMap::new();

        for name in names.iter() {
            for part in parts.iter() {
                properties.insert(name.to_string(), part);
            }
        }

        Self { properties }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn new_entity() {
        assert_eq!(2, 2)
    }
}