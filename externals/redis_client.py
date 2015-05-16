from redis import StrictRedis


class RedisClient(StrictRedis):

    def get_bool(self, key):
        return self.get(key) == 'true'
