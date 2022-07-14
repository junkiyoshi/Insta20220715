#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	for (int x = -300; x <= 300; x += 30) {

		for (int y = -300; y <= 300; y += 30) {

			this->setBoxToMesh(this->face, this->line, glm::vec3(x, y, 0), 20);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(0);
	this->face.draw();

	ofSetColor(255);
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth) {

	int face_index = face_target.getNumVertices();
	int frame_index = frame_target.getNumVertices();

	vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	vertices.push_back(glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	vertices.push_back(glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	vertices.push_back(glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	vertices.push_back(glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	vertices.push_back(glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	vertices.push_back(glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	vertices.push_back(glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	for (auto& vertex : vertices) {

		auto noise_deg = glm::vec3(
			ofMap(ofNoise(glm::vec4((location + vertex) * 0.0035, ofGetFrameNum() * 0.005)), 0, 1, -360, 360),
			ofMap(ofNoise(glm::vec4((location + vertex) * 0.0035, ofGetFrameNum() * 0.005)), 0, 1, -360, 360),
			ofMap(ofNoise(glm::vec4((location + vertex) * 0.0035, ofGetFrameNum() * 0.005)), 0, 1, -360, 360));

		auto rotation_x = glm::rotate(glm::mat4(), noise_deg.x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), noise_deg.y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), noise_deg.z * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

		face_target.addVertex(location + glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_z);
		frame_target.addVertex(location + glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_z);
	}

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);
	face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

	face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 4);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 3);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 0);

	frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	frame_target.addIndex(frame_index + 7); frame_target.addIndex(frame_index + 4);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}