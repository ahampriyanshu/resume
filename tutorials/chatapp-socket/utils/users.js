const users = [];

function userJoined(id, username, room) {
  const user = { id, username, room };

  users.push(user);

  return user;
}

function getCurrentUser(id) {
  return users.find((user) => user.id === id);
}

function userLeave(id) {
  const index = users.findIndex((user) => user.id === id);
  return index !== -1 && users.splice(index, 1)[0];
}

function getRoomUsers(room) {
  return users.filter((user) => user.room === room);
}

module.exports = { userJoined, getCurrentUser, userLeave, getRoomUsers };
